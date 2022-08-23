/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:33 by akadi             #+#    #+#             */
/*   Updated: 2022/08/23 15:19:53 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_cd(char **cmd)
{
	if (*cmd && !*(cmd + 1))
	{
		if (chdir(getenv("HOME")) == -1)
			check_folder (getenv("HOME"));
	}
	else
	{
		if (chdir(*(cmd + 1)) == -1)
			check_folder (*(cmd + 1));
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
	int	i;
	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "0") || ft_atoi(cmd[i]) > 0 \
				|| ft_atoi(cmd[i]) < 0)
		{	
			g_tools.status_sign = ft_atoi(cmd[i]);
			printf("exit \n");
			exit (EXIT_FAILURE);
		}
		if (ft_atoi(cmd[i]) == 0)
		{
			printf("exit \nminishell: exit: %s: \
			numeric argument required\n", cmd[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	printf("exit\n");
	exit(EXIT_FAILURE);
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
