/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:12:27 by akadi             #+#    #+#             */
/*   Updated: 2022/08/19 09:46:37 by yoelhaim         ###   ########.fr       */
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

void	print_cmnd(char **cmd)
{
	char	*tmp;
	char	**splited_path;

	tmp = *cmd;
	splited_path = ft_split(get_path(), ':');
	while (*splited_path)
	{
		execve(ft_strjoin(ft_strjoin("/", *splited_path), \
		ft_strjoin("/", cmd[0])), cmd, export_env(g_tools.g_env));
		splited_path++;
	}
}

void	cmd_system(char **cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		print_cmnd(cmd);
		exit(1);
	}
	else
		pid = wait(NULL);
}

void	exec_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (*(tmp->cmnd) == NULL)
		{
			return ;
		}
		if (check_builtin(*(tmp->cmnd)))
			printf(" build => %s\n", *(tmp->cmnd));
		else
			cmd_system(tmp->cmnd);
		tmp = tmp->next;
	}
}
