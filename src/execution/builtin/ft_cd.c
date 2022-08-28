/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 14:27:28 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 16:09:58 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	check_switch_cd(void)
{
	static int	status;
	static int	is_switch;
	char		path[1024];
	t_env		*env;

	env = g_tools.g_env;
	while (env)
	{	
		if (!ft_strcmp(env->variable, "OLDPWD"))
			status = 1;
		env = env->next;
	}
	if (status == 0)
		ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
	else
	{
		if (is_switch == 1)
		{
			if (chdir(getenv("OLDPWD")) == -1)
				check_folder (getenv("OLDPWD"));
			is_switch = 0;
		}
		else
		{
			if (chdir(getenv("PWD")) == -1)
				check_folder (getenv("PWD"));
			is_switch = 1;
		}
		printf("%s\n", getcwd(path, 1024));
	}
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
	if (status_pwd)
		pushback_env(&g_tools.g_env, ft_strdup("PWD"), \
		ft_strdup(ft_strjoin("PWD=", getcwd(path, 1024))));
	if (status_old)
		pushback_env(&g_tools.g_env, ft_strdup("OLDPWD"), \
		ft_strdup(ft_strjoin("OLDPWD=", last_cmd)));
}

void	ft_cd(char **cmd)
{
	char	path[1024];
	char	*this_path;

	this_path = getcwd(path, 1024);
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
