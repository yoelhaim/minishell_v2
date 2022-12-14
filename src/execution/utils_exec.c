/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:34:27 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 20:41:40 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*set_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			printf("%c", str[i]);
		i++;
	}
	return (str);
}

char	**export_env(t_env *env)
{
	t_env	*tmp;
	int		len;
	char	**exported_env;
	int		i;
	char	**forfree;

	i = 0;
	len = 0;
	tmp = env;
	exported_env = NULL;
	while (tmp && ++len)
		tmp = tmp->next;
	exported_env = malloc(sizeof(char *) * len++);
	if (!exported_env)
		return (NULL);
	add(&g_tools.garbage, exported_env);
	while (env)
	{
		exported_env[i++] = env->value;
		env = env->next;
	}
	exported_env[i] = NULL;
	forfree = exported_env;
	return (forfree);
}

char	*get_path(void)
{
	t_env	*env;

	env = g_tools.g_env;
	while (env)
	{
		if (ft_strstr(env->variable, "PATH"))
			return (ft_strstr(env->value, "=") + 1);
		env = env->next;
	}
	return (NULL);
}

int	size_word(char **cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return (ERROR_RETURN);
	while (cmd[i])
		i++;
	return (i);
}
