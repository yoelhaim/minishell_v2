/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:27:28 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 18:22:08 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	push_the_env(int status_pwd, int status_old, char *path, char *last_cmd)
{
	if (status_pwd)
		pushback_env(&g_tools.g_env, ft_strdup("PWD"), \
		ft_strdup(ft_strjoin("PWD=", getcwd(path, 1024))));
	if (status_old)
		pushback_env(&g_tools.g_env, ft_strdup("OLDPWD"), \
		ft_strdup(ft_strjoin("OLDPWD=", last_cmd)));
}

void	change_pwd(char *last_cmd)
{
	t_env	*env;
	char	path[1024];
	bool	status_old;
	bool	status_pwd;

	status_old = true;
	status_pwd = true;
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strcmp(env->variable, "PWD"))
		{
			env->value = ft_strdup(ft_strjoin("PWD=", getcwd(path, 1024)));
			status_pwd = false;
		}
		if (!ft_strcmp(env->variable, "OLDPWD"))
		{
			env->value = ft_strdup(ft_strjoin("OLDPWD=", last_cmd));
			status_old = false;
		}
		env = env->next;
	}
	push_the_env(status_pwd, status_old, path, last_cmd);
}

void	ft_cd(char **cmd)
{
	char	path[1024];
	char	*this_path;

	this_path = getcwd(path, 1024);
	if (this_path == NULL)
		return ;
	if (*cmd && (!*(cmd + 1) || *(cmd + 1)[0] == '~'))
	{
		if (chdir(getenv("HOME")) == -1)
			check_folder (getenv("HOME"));
		else
			change_pwd(this_path);
	}
	else if (*cmd && *(cmd + 1)[0] == '-')
		check_switch_cd();
	else
	{
		if (chdir(*(cmd + 1)) == -1)
			check_folder (*(cmd + 1));
		else
			change_pwd(this_path);
	}
}
