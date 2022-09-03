/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:14:01 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 17:20:49 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_switcher(void)
{
	static int	is_switch;
	char		*old;
	char		*new;
	t_env		*temp;

	temp = g_tools.g_env;
	while (temp)
	{
		if (!ft_strcmp(temp->variable, "PWD"))
			new = ft_strstr(temp->value, "=") + 1;
		if (!ft_strcmp(temp->variable, "OLDPWD"))
			old = ft_strstr(temp->value, "=") + 1;
		temp = temp->next;
	}
	if (is_switch == 0)
	{
		chdir(old);
			is_switch = 1;
	}
	else
	{
		chdir(new);
		is_switch = 0;
	}
}

void	check_switch_cd(void)
{
	t_env		*env;
	static int	status;
	char		path[PATH_MAX];

	env = g_tools.g_env;
	while (env)
	{	
		if (!ft_strcmp(env->variable, "OLDPWD"))
			status = 1;
		env = env->next;
	}
	if (status == 0)
	{
		ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
		return ;
	}
	else
	{
		ft_switcher();
		getcwd(path, PATH_MAX);
		printf("%s\n", path);
	}
}
