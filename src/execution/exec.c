/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 12:28:53 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/01 12:55:53 by yoelhaim         ###   ########.fr       */
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

void	pipe_cmd(t_cmd *cmd, int statuss)
{
	pid_t	pid;
	int		status;

	status = 1;
	g_tools.fdd = 0;
	while (cmd)
	{
		// pipe(g_tools.fd);
		if (pipe(g_tools.fd))
			return ;
		pid = fork();
		if (pid < 0)
			return ;
		else if (pid == 0)
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
		if (waitpid(-1, &statuss, 0) == -1)
			break ;
	}
	if (WIFEXITED(statuss))
		g_tools.status_sign = WEXITSTATUS(statuss);
	else if (WIFSIGNALED(statuss))
		g_tools.status_sign = 128 + WTERMSIG(statuss);
}

void	hendl(int c)
{
	(void) c;
	g_tools.status_sign = 130;
}

void	exec_cmd(t_cmd *cmd, t_node *list)
{
	int	status;

	signal(SIGINT, hendl);
	status = 1;
	
	if (g_tools.status_sign == 127)
		g_tools.status_sign = 0;
	if (check_is_one_cmnd(cmd, list, &status))
		return ;
	else
		pipe_cmd(cmd, status);
}
