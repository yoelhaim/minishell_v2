/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:12:27 by akadi             #+#    #+#             */
/*   Updated: 2022/08/18 20:56:00 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo")|| !ft_strcmp(cmd, "cd")\
	|| !ft_strcmp(cmd, "export")||!ft_strcmp(cmd, "unset")\
	||!ft_strcmp(cmd, "exit")||!ft_strcmp(cmd, "pwd")\
	||!ft_strcmp(cmd, "env"))
		return(1);
	return (0);
} 

void print_cmnd(char  **cmd)
{
	char *tmp;
	tmp = *cmd;
	
	printf("zawa9a => %s\n", cmd[0]);
	execve("/bin/ls", cmd, &g_tools.g_env->value);
}

void cmd_system(char  **cmd)
{
	int pid;
	pid = fork();
	if(pid == -1)
		return ;
	if (pid == 0)
	{
		 print_cmnd(cmd);
		exit(EXIT_SUCCESS);	
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
		if(*(tmp->cmnd) == NULL)
		{
			return ;
		}
		if (check_builtin(*(tmp->cmnd)))
			printf("%s\n", *(tmp->cmnd));
		else
			cmd_system(tmp->cmnd);
		tmp = tmp->next;
	}
}