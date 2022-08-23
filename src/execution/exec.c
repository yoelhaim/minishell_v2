/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 20:12:27 by akadi             #+#    #+#             */
/*   Updated: 2022/08/23 17:04:54 by yoelhaim         ###   ########.fr       */
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

void	print_cmnd(char **cmd, int *stt)
{
	char	**splited_path;
	char	*path;
	
	(void ) cmd;
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
		g_tools.status_sign = WEXITSTATUS(stt);
		
}

void	cmd_system(char **cmd, t_cmd **cmd_list, int count_cmd, int fd[2])
{
	g_tools.status_sign = 127;
	 (void) cmd_list;
	 if(count_cmd == 0)	// ls
		{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		print_cmnd(cmd, &g_tools.status_sign);
		}
		else if(count_cmd > 0)  //wc 
		{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		print_cmnd(cmd, &g_tools.status_sign);
		}
	
	
}

void	exec_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	
	int		count_cmd = 0;
	int		pid;
	int		n_of_pipe =size_of_cmd(&tmp);
	int fd[n_of_pipe];
	
	tmp =cmd;
	if(n_of_pipe > 1)
	{
		while(n_of_pipe > 1)
		{
			pipe(fd);
			n_of_pipe--;
		}
	}
	while (tmp)
	{
		if (*(tmp->cmnd) == NULL)
		{
			check_redirecrt(tmp->red);
			return ; // rederiction
		}
		if (check_builtin(*(tmp->cmnd)))
			{
				if(g_tools.status_sign == 256)
					g_tools.status_sign = 1;
				else
					g_tools.status_sign = 0;
				ft_builtin(tmp->cmnd);
			}
		else
		{
			pid = fork();
			if(pid == 0)
			{
				cmd_system(tmp->cmnd, &cmd, count_cmd, fd);
			}
				
		}
		count_cmd++;
		tmp = tmp->next;
	
	}
	if (size_of_cmd(&cmd) > 1 )
	{close(fd[0]);
	close(fd[1]);}
	while(waitpid(-1, NULL, 0) != -1);
	
}
