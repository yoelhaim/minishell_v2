/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:27:28 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/02 16:18:52 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	push_the_env(int status_pwd, int status_old, char *last_cmd)
{
	if (status_pwd)
		pushback_env(&g_tools.g_env, ft_strdup("PWD"), \
				ft_strdup(ft_strjoin("PWD=", ft_getcwd())));
	if (status_old && last_cmd != NULL)
		pushback_env(&g_tools.g_env, ft_strdup("OLDPWD"), \
				ft_strdup(ft_strjoin("OLDPWD=", last_cmd)));
}

void	change_pwd(char *last_cmd)
{
	t_env	*env;
	bool	status_old;
	bool	status_pwd;

	status_old = true;
	status_pwd = true;
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strcmp(env->variable, "PWD"))
		{
			env->value = ft_strdup(ft_strjoin("PWD=", ft_getcwd()));
			status_pwd = false;
		}
		if (!ft_strcmp(env->variable, "OLDPWD") && last_cmd != NULL)
		{
			env->value = ft_strdup(ft_strjoin("OLDPWD=", last_cmd));
			status_old = false;
		}
		env = env->next;
	}
	push_the_env(status_pwd, status_old, last_cmd);
}

void	ft_cd(char **cmd)
{
	char	*this_path;

	this_path = ft_getcwd();
	if (*(cmd + 1) != NULL )
	{
		if (!ft_strcmp(*(cmd + 1), "."))
		{
			if (chdir(this_path) == -1)
				ft_putstr_fd(MESSAGE_NF_FOLDER, 2);
			return ;
		}
	}
	if (*cmd && (*(cmd + 1) == NULL || !ft_strcmp(*(cmd + 1), "~")))
	{
		chdir(getenv("HOME"));
		change_pwd(this_path);
	}
	else if (*cmd && *(cmd + 1)[0] == '-')
		check_switch_cd();
	else
	{
		more_cd(*(cmd + 1), this_path);
	}
}
