/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 12:28:53 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/07 17:52:48 by yoelhaim         ###   ########.fr       */
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
		g_tools.dup_in = dup(0);
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
	while (cmd)
	{
		if (pipe(g_tools.fd) < 0)
			return ;
		pid = fork();
		if (!check_pid(pid))
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
		if (waitpid(-1, &statuss, 0) == -1)
			break ;
	handl_signal(&statuss);
}

void	hendl(int c)
{
	if (c == 3)
		ft_putstr_fd("QUIT", 2);
	write(1, "\n", 1);
	g_tools.status_sign = 128 + WTERMSIG(c);
}

void	exec_cmd(t_cmd *cmd, t_node *list)
{
	int	status;

	g_tools.fdd = 0;
	status = 1;
	if (g_tools.status_sign == 127)
		g_tools.status_sign = 0;
	if (check_is_one_cmnd(cmd, list, &status))
		return ;
	else
		pipe_cmd(cmd, status);
}
