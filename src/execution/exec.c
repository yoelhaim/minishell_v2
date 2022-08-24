/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:19:40 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/24 22:19:45 by yoelhaim         ###   ########.fr       */
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

int	print_cmnd(char **cmd, int *stt)
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
	return(ERROR_RETURN);
		
}

int	cmd_system(t_cmd *cmd_list,int  fd[2])
{
	int	fd_help;
	int	pid;

	g_tools.status_sign = 127;
	while (cmd_list)
	{
	pipe(fd);
	if ((pid = fork()) == -1)
		exit(1);
	else if (pid == 0)
	{
		dup2(fd_help, 0);
		if (size_of_cmd(&cmd_list) != 1)
		{
			dup2(fd[1], 1);
		}
		if(print_cmnd(cmd_list->cmnd, &g_tools.status_sign) == ERROR_RETURN)
			return(ERROR_RETURN);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		fd_help = fd[0];
		cmd_list = (cmd_list->next);
	}
	}
	close(fd[0]);
		close(fd[1]);	

	return(1);
}

void	exec_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	
	int		fd[2];
	
	tmp = cmd;
// printf("size %d\n", size_of_cmd(&cmd) );
		if (*(tmp->cmnd) == NULL)
		{
			check_redirecrt(tmp->red);
			return ; // rederiction
		}
		if (check_builtin(*(tmp->cmnd)))
		{
				ft_builtin(tmp->cmnd);
		}
		// if(!ft_strcmp(*(tmp->cmnd), "cd") && size_of_cmd(&cmd) > 1)
		// 	tmp++;
		else
		{
			if(cmd_system(cmd, fd) == ERROR_RETURN)
				exit(1) ;
		
				if(errno == ENOENT)
					exit(127);
				if(errno == EACCES)
					exit(126);	
		}	
}
