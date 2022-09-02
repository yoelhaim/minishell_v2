/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:07:57 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/02 01:05:33 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_is_valid_var(char *arg, int is_egal)
{
	while (*arg)
	{
		if (is_egal)
		{
			if (!ft_isalnum(*arg) && (*arg != '_'))
				return (-2);
		}
		if (!ft_isalnum(*arg) && (*arg != '_' && *arg != '+'))
			return (-1);
		arg++;
	}
	return (1);
}

void	add_new_var_env(char *var, char *val)
{
	char	*temp_var;

	if (!val)
		temp_var = var;
	else
		temp_var = ft_strdup(ft_strjoin(ft_strjoin(var, "="), val));
	pushback_env(&g_tools.g_env, ft_strdup(var), temp_var);
}

void	update_var_env(char *var, char *val, int is_append)
{
	char	*temp_var;
	t_env	*env;

	env = g_tools.g_env;
	if (!val)
		temp_var = var;
	else
		temp_var = ft_strdup(ft_strjoin(ft_strjoin(var, "="), val));
	while (env)
	{
		if (!ft_strcmp(env->variable, var))
		{
			if (is_append)
				env->value = ft_strjoin(temp_var, val);
			else
				env->value = temp_var;
			break ;
		}
		env = env->next;
	}
}

int	checkappend(char *cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		if (*cmd == '+' && *(cmd + 1) == '=')
			return (1);
		cmd++;
	}
	return (0);
}

int	err_arg(char **cmd)
{
	if (!*cmd)
		return (1);
	while (*cmd)
	{
		if (*cmd[0] < 'a' || *cmd[0] > 'z')
			return (1);
		cmd++;
	}
	return (0);
}
