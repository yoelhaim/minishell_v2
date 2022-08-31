/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 20:24:16 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/31 23:16:14 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_status_file(int status)
{
	if (status)
	{
		dup2(g_tools.dup_out, 1);
		close(g_tools.dup_out);
	}
	else
	{
		dup2(g_tools.dup_in, 0);
		dup2(g_tools.dup_out, 1);
		close(g_tools.dup_out);
		close(g_tools.dup_in);
	}
}

void	check_status_exit(char *cmd)
{
	if (errno == ENOENT || errno == EFAULT)
		ft_putstr_fd(create_err("minishell : " \
		, cmd, ": command not found \n"), 2);
	else if (errno == EACCES)
		ft_putstr_fd(create_err("minishell : " \
		, cmd, ": : Permission denied \n"), 2);
	else
		ft_putstr_fd("errrr", 2);
}

int	cmd_systm_one(t_cmd *cmd)
{
	int	pid;
	int	status;
	int	statuss;

	pid = fork();
	status = 1;
	if (pid == 0)
	{
		if (check_redirecrt(cmd->red, &status) == ERROR_RETURN)
			exit(0);
		exit(print_cmnd(cmd->cmnd));
	}
	while (1)
	{
		if (waitpid (-1, &statuss, 0) == -1)
			break ;
	}
	check_status_file(status);
	g_tools.status_sign = WEXITSTATUS(statuss);
	return (1);
}

int	check_is_one_cmnd(t_cmd *cmd, t_node *list, int *status)
{
	
	int i =0;
	while (list)
	{
		if (list->type == PIPE)
			i++;
		list = list->next;
	}
	if (i == 0)
	{	
		g_tools.dup_out = dup(1);
	    g_tools.dup_in = dup(0);
		if (*cmd->cmnd == NULL)
			if (check_redirecrt(cmd->red, status) == ERROR_RETURN)
				return (check_status_file(*status), 1);
		if (*cmd->cmnd != NULL)
		{
			if (check_builtin(*cmd->cmnd))
			{
				if (check_redirecrt(cmd->red, status) == ERROR_RETURN)
					return (check_status_file(*status), 1);
				ft_builtin(cmd->cmnd, status);
			}
			else
				cmd_systm_one(cmd);
		}
		return (check_status_file(*status), 1);
	}
	return (0);
}

void	child_process(t_cmd *cmd, int *status)
{
	close(g_tools.fd[0]);
	if (g_tools.fdd != 0)
	{
		dup2(g_tools.fdd, 0);
		close(g_tools.fdd);
	}
	if (cmd->next != NULL)
	{
		close(g_tools.fd[0]);
		dup2(g_tools.fd[1], 1);
	}
	close(g_tools.fd[1]);
	is_red(cmd->red, status);
	if (check_builtin(*(cmd->cmnd)))
	{
		if (g_tools.status_sign == 127)
			g_tools.status_sign = 1;
		else
			g_tools.status_sign = 0;
		ft_builtin(cmd->cmnd, status);
		exit(1);
	}
	else
		exit(print_cmnd(cmd->cmnd));
}
