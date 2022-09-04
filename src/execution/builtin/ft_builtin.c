/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:33 by akadi             #+#    #+#             */
/*   Updated: 2022/09/03 20:15:53 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_env(char **cmd)
{
	t_env	*env;

	env = g_tools.g_env;
	if (*(cmd + 1))
	{
		g_tools.status_sign = 1;
		ft_putstr_fd(create_err("env: ",*(cmd + 1) \
					, ": Too MAnt Argument \n"), 2);
		return ;
	}
	while (env)
	{
		if (ft_strstr(env->value, "="))
			ft_putstr_fd(ft_strjoin(env->value, "\n"), 1);
		env = env->next;
	}
	g_tools.status_sign = 0;
}

int	ft_is_number(char n)
{
	if (n < '0' || n > '9')
		return (0);
	return (1);
}

int	check_isvalid_number(char *str, char *cmd)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_is_number(str[i]))
		{
			return (ft_putstr_fd(create_err("exit \nminishell: exit: ", cmd, \
							" numeric argument required\n"), 2), 0);
		}
	}
	return (1);
}

void	ft_exit(char **cmd)
{
	char	*str;

	str = *(cmd + 1);
	if (*cmd && *(cmd + 1) == NULL)
	{
		ft_putstr_fd("exit\n", 2);
		exit (0);
	}
	cmd++;
	if (!check_isvalid_number(str, *cmd))
		exit(255);
	if (*(cmd +1) == NULL)
	{	
		g_tools.status_sign = ft_atoi(*cmd);
		printf("exit \n");
		exit (ft_atoi(*cmd));
	}
	if (*++cmd)
	{
		ft_putstr_fd(create_err("exit \nminishell: exit: ",*cmd, \
					" oo many arguments\n"), 2);
		return ;
	}
}

void	ft_builtin(char **cmd, int *status)
{
	*cmd = remove_back_slash(*cmd);
	if (!ft_strcmp(*cmd, "cd"))
		ft_cd(cmd);
	if (!ft_strcmp(*cmd, "exit"))
		ft_exit (cmd);
	if (!ft_strcmp(*cmd, "env"))
		ft_env(cmd);
	if (!ft_strcmp(*cmd, "export"))
		ft_export(cmd);
	if (!ft_strcmp(*cmd, "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(*cmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(*cmd, "unset"))
		g_tools.g_env = ft_unset(cmd);
	*status = 0;
}
