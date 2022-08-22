/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:12:27 by akadi             #+#    #+#             */
/*   Updated: 2022/08/22 22:18:39 by yoelhaim         ###   ########.fr       */
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

void handler_sig(int pid)
{
	(void)pid;
	printf("10000000\n");
	
}
void	print_cmnd(char **cmd)
{
	char	**splited_path;
	char	*path;
	(void ) cmd;
	// int		status_cmnd;
	// int		status_access;
	signal(SIGINT, handler_sig);
	splited_path = ft_split(get_path(), ':');
	if (!access(*cmd, X_OK))
		path = *cmd;
	else
	{	
		while (*splited_path)
		{
			path = ft_strjoin(*splited_path,ft_strjoin("/", cmd[0]));
			if(!access(path, X_OK))
				break;
		splited_path++;
	}
	}
	execve(path, cmd, export_env(g_tools.g_env));
		
		printf("minishell : %s : command not found \n", *cmd );
		
		
}

void	cmd_system(char **cmd)
{
	int	pid;
	int fd[2];
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		print_cmnd(cmd);
		exit(1);
	}
	else
		pid = wait(NULL);
	close(fd[0]);
	close(fd[1]);
}

void	exec_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (*(tmp->cmnd) == NULL)
		{
			check_redirecrt(tmp->red);
			return ; // rederiction
		}
		if (check_builtin(*(tmp->cmnd)))
			ft_builtin(tmp->cmnd);
		else
			cmd_system(tmp->cmnd);
		tmp = tmp->next;
	}
}
