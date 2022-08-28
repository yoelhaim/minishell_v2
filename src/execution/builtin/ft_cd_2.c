/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:14:01 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 18:22:11 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_switcher(void)
{
	static int	is_switch;

	if (is_switch == 1)
	{
		chdir(getenv("OLDPWD"));
		is_switch = 0;
	}
	else
	{
		chdir(getenv("PWD"));
			is_switch = 1;
	}
}

void	check_switch_cd(void)
{
	char		path[1024];
	t_env		*env;
	static int	status;

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
		ft_switcher();
		printf("%s\n", getcwd(path, 1024));
	}
}
