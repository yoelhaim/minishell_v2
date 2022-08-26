/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 12:28:53 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/26 17:56:31 by yoelhaim         ###   ########.fr       */
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
			free(path);
			free(*splited_path);
		splited_path++;
	}
	}
	execve(path, cmd, export_env(g_tools.g_env));
		
	printf("minishell : %s : command not found \n", *cmd );
	
	return(ERROR_RETURN);
		
}
int cmd_systm_one(t_cmd *cmd)
{
	int pid;
	int	statuss;
	int out;
	out = dup(1);
	int in = dup(0);
	int status = 1;
	
	(void)in;
	pid = fork();
	if(pid == 0)
	{
		if(check_redirecrt(cmd->red,&status) == ERROR_RETURN)
			return(1);
		print_cmnd(cmd->cmnd);
		exit(127);
	}
	waitpid(-1, &statuss, 0);
	if(status)
		{
		  dup2(out , 1);
		  close(out);
		}
	g_tools.status_sign = WEXITSTATUS(statuss);
	return (1);
}

// int	cmd_system(t_cmd *cmd_list,int  fd[2], t_cmd *tmp)
// {
// 	int	fd_help;
// 	int	pid;
// 	int	status;

// 	fd_help = 0;
// 	while (cmd_list)
// 	{
// 		if(size_of_cmd(&tmp) != 1)
// 			pipe(fd);
// 		if ((pid = fork()) == -1)
// 			exit(1);
// 		else if (pid == 0)
// 		{
// 			dup2(fd_help, 0);
// 			if (size_of_cmd(&cmd_list) != 1)
// 			{
// 				dup2(fd[1], 1);
// 				close(fd[1]);
// 			}
// 			if(print_cmnd(cmd_list->cmnd, &g_tools.status_sign) == ERROR_RETURN)
// 				return(ERROR_RETURN);
// 		}
// 		else
// 		{
// 			waitpid(-1, &status, 0);
// 			if (size_of_cmd(&tmp) != 1)
// 				close(fd[1]);
// 			fd_help = fd[0];
// 			cmd_list = (cmd_list->next);
// 		}
// 		g_tools.status_sign = WEXITSTATUS(status);
// 	}
// 	if (size_of_cmd(&tmp) != 1)
// 	{close(fd[0]);
// 	close(fd[1]);}	

// 	return(1);
// }
int 	check_is_one_cmnd(t_cmd *cmd, t_node *list)
{
	int	i;
	int out;
	out = dup(1);
	int in = dup(0);
	int status = 1;
	i = 0;
	while (list)
	{
		if(list->type ==  PIPE)
			i++;
		list = list->next;
	}
	if(i == 0)
	{	
		if(check_redirecrt(cmd->red, &status) == ERROR_RETURN)
			return(1);
		if(*cmd->cmnd != NULL)
		{
		if(check_builtin(*cmd->cmnd))
			ft_builtin(cmd->cmnd);
		else
			cmd_systm_one(cmd);
		}
		if(status)
		{
		  dup2(out , 1);
		  close(out);
		}
		else
		{
		 dup2(in , 0);
		  close(in);
		  dup2(out , 1);
		  close(out);
		}
		return(1);
	}
	return(0);
}


void	exec_cmd(t_cmd *cmd, t_node *list)
{
	if(check_is_one_cmnd(cmd, list))
		return ;
	
	
}

// void	exec_cmd(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int		fd[2];
	
// 	tmp = cmd;
// 		if (*(tmp->cmnd) == NULL)
// 		{
// 			check_redirecrt(tmp->red);
// 			return ; // rederiction
// 		}
		
// 		if (check_builtin(*(tmp->cmnd)) )
// 		{
// 			if (g_tools.status_sign == 127)
// 			  g_tools.status_sign = 1;
// 			else
// 				g_tools.status_sign = 0;
// 			if(size_of_cmd(&cmd) != 1)
// 			{
// 			pipe(fd);
// 			pid =fork();
// 			if(pid == 0)
// 			{
				
// 				dup2(fd[1], 1);
// 				close(fd[1]);
// 				ft_builtin(tmp->cmnd);
// 				exit(1);
// 			}
// 			else
// 				pid = wait(NULL);
// 			}
// 			else
// 				{
// 					ft_builtin(tmp->cmnd);
// 					return ;
// 				}
// 		}
		
// 		 if(cmd_system(cmd, fd, tmp) == ERROR_RETURN )
// 		{		
// 			exit(127) ;
// 		if(errno == ENOENT)
// 			exit(127);
// 		if(errno == EACCES)
// 			exit(126);	}
		
// }
