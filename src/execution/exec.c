/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 12:28:53 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/30 11:48:15 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") \
			|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export") \
			|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit") \
			|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

int	print_cmnd(char **cmd)
{
	char	**splited_path;
	char	*path;

	(void ) cmd;
	path = get_path();
	if (!path)
		splited_path = ft_split("", ':');
	else
		splited_path = ft_split(path, ':');
	if (!access(*cmd, X_OK))
		path = *cmd;
	else if (strchr(*cmd, '/')) // TODO : use builtin instead of
		path = *cmd;
	else
	{	
		while (*splited_path)
		{
			path = ft_strjoin(*splited_path, ft_strjoin("/", cmd[0]));
			if (!access(path, X_OK))
				break ;
			free(path);
			free(*splited_path);
			splited_path++;
		}
	}
	execve(path, cmd, export_env(g_tools.g_env));
	ft_putstr_fd(create_err("minishell : ", *cmd, ": command not found \n"), 2);
	if (errno == ENOENT)
		return (127);
	else if(errno == EACCES)
		return (126);
	return (ERROR_RETURN);
}

void	is_red(t_red *cmd, int *status)
{
	t_red	*red;

	red = cmd;
	while (red)
	{
		if (check_redirecrt(cmd, status) != ERROR_RETURN)
			return ;
		red = red->next;
	}
}

void	pipe_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 1;
	while (cmd)
	{
		pipe(g_tools.fd);
		pid = fork();
		if (pid == 0)
			child_process(cmd, &status);
		close(g_tools.fd[1]);
		if (g_tools.fdd != 0)
			close(g_tools.fdd);
		if (!cmd->next)
			close(g_tools.fd[0]);
		g_tools.fdd = g_tools.fd[0];
		cmd = cmd->next;
	}
	while (1)
	{
		if (wait(NULL) == -1)
			break ;
	}
}

void	exec_cmd(t_cmd *cmd, t_node *list)
{
	int	i;
	int	status;

	status = 1;
	g_tools.dup_out = dup(1);
	g_tools.dup_in = dup(0);
	i = 0;
	if (g_tools.status_sign == 127)
		g_tools.status_sign = 0;
	if (check_is_one_cmnd(cmd, list, &i, &status))
		return ;
	else
		pipe_cmd(cmd);
}
