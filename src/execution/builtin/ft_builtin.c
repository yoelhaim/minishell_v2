/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:33 by akadi             #+#    #+#             */
/*   Updated: 2022/08/25 19:07:06 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	change_pwd(char *last_cmd)
{
	t_env	*env;
	char	path[1024];

	env = g_tools.g_env;
	while(env)
	{
		if(!ft_strcmp(env->variable, "PWD"))
			env->value = ft_strdup(ft_strjoin("PWD=", getcwd(path, 1024) ));
		if(!ft_strcmp(env->variable, "OLDPWD"))
			env->value = ft_strdup(ft_strjoin("OLD_PWD=", last_cmd));
		env = env->next;
	}
}

void	ft_cd(char **cmd)
{
	char	path[1024];
	char	*this_path;

	this_path = getcwd(path, 1024);
	if (*cmd && !*(cmd + 1))
	{
		if (chdir(getenv("HOME")) == -1)
			check_folder (getenv("HOME"));
		else
			change_pwd(this_path);
	}
	else
	{
		if (chdir(*(cmd + 1)) == -1)
			check_folder (*(cmd + 1));
		else
			change_pwd(this_path);
	}
}

void	ft_env(char **cmd)
{
	t_env	*env;

	env = g_tools.g_env;
	if (*(cmd + 1))
	{
		printf("env: %s: No such file or directory\n",*(cmd + 1));
		return ;
	}
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}

void	ft_exit(char **cmd)
{
	cmd++;
	if ((!ft_strcmp(*cmd, "0") || ft_atoi(*cmd) > 0 \
				|| ft_atoi(*cmd) < 0) && *(cmd +1) == NULL)
		{	
			g_tools.status_sign = ft_atoi(*cmd);
			printf("exit \n");
			exit (ft_atoi(*cmd));
		}
		
		if (ft_atoi(*cmd) == 0)
		{
			printf("exit \nminishell: exit: %s: numeric argument required\n", *cmd);
			exit(255);
		}
	if(*++cmd)
	{	
		printf("exit \nminishell: exit: %s: oo many arguments\n", *cmd);
		return ;
	}
}

void	ft_builtin(char **cmd)
{
	if (!ft_strcmp(*cmd, "exit"))
		ft_exit (cmd);
	if (!ft_strcmp(*cmd, "env"))
		ft_env(cmd);
	if (!ft_strcmp(*cmd, "export"))
		ft_export(cmd);
	if (!ft_strcmp(*cmd, "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(*cmd, "cd"))
		ft_cd(cmd);
	if (!ft_strcmp(*cmd, "pwd"))
		ft_pwd(*(cmd + 1));
	if (!ft_strcmp(*cmd, "unset"))
		g_tools.g_env = ft_unset(cmd);
}
