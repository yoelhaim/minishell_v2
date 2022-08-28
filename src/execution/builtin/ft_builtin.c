/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:33 by akadi             #+#    #+#             */
/*   Updated: 2022/08/28 21:41:17 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_env(char **cmd)
{
	t_env	*env;

	env = g_tools.g_env;
	if (*(cmd + 1))
	{
		ft_putstr_fd(create_err("env: ",*(cmd + 1) \
		, ": No such file or directory\n"), 2);
		return ;
	}
	while (env)
	{
		if (strstr(env->value, "="))
			printf("%s\n", env->value);
		env = env->next;
	}
}

void	ft_exit(char **cmd)
{
	if (*cmd && *(cmd + 1) == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit (0);
	}
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
		ft_putstr_fd(create_err("exit \nminishell: exit: ",*cmd, \
		" numeric argument required\n"), 2);
		exit(255);
	}
	if (*++cmd)
	{	
		ft_putstr_fd(create_err("exit \nminishell: exit: ",*cmd, \
		" oo many arguments\n"), 2);
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
		ft_pwd();
	if (!ft_strcmp(*cmd, "unset"))
		g_tools.g_env = ft_unset(cmd);
}
