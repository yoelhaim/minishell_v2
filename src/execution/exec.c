/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 12:28:53 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/27 17:44:46 by akadi            ###   ########.fr       */
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
		else
		{
		 dup2(in , 0);
		 close(in);
		 dup2(out , 1);
		 close(out);
		}	
	g_tools.status_sign = WEXITSTATUS(statuss);
	return (1);
}

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

int is_red(t_red *cmd, int *fdd, int *status)
{
	t_red *red;
	(void) fdd;
	red = cmd;
	(void) status;
	while (red)
	{
		if(check_redirecrt(cmd, status) == ERROR_RETURN)
			return 1;
		*fdd = g_tools.w_out;
		red = red->next;
	}
	return (0);
}

void	pipe_cmd(t_cmd *cmd, t_node *list)
{
	(void)list;
	int fd[2];
	pid_t pid;
	int status = 1;		
	while (cmd) 
	{

		pipe(fd);
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			if (is_red(cmd->red, &g_tools.fdd, &status))
				exit(1);
			close(fd[0]);
			if (g_tools.fdd != 0)
			{
				dup2(g_tools.fdd, 0);
				close(g_tools.fdd);
			}
			if (cmd->next != NULL) {
				close(fd[0]);
				dup2(fd[1], 1);
			}
			close(fd[1]);
			if (check_builtin(*(cmd->cmnd)) )
		{
			if (g_tools.status_sign == 127)
			  g_tools.status_sign = 1;
			else
				g_tools.status_sign = 0;
				ft_builtin(cmd->cmnd);
				exit(1);
			}
			else 
			{
					print_cmnd(cmd->cmnd);
					exit(1);
			}
		}
			close(fd[1]);
			if (g_tools.fdd != 0)
				close(g_tools.fdd);
			if (!cmd->next)
				close(fd[0]);
			g_tools.fdd = fd[0];
			cmd = cmd->next;	
	}	
	while(1)
		{
			if (wait(NULL) == -1)
				break;
		}
}
void	exec_cmd(t_cmd *cmd, t_node *list)
{
	if(check_is_one_cmnd(cmd, list))
		return ;
	else
		pipe_cmd(cmd, list);
}
