/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:34:27 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/18 23:48:55 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *setUpper(char *s)
{
	char *str= s;
	int i = 0;
	while(str[i])
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		printf("%c", str[i]);
		i++;
	}
	return(str);
}
char **export_env(t_env *env)
{
	t_env *tmp;
	int len;
	char **exported_env;
	int i;

	i = 0;
	len = 0;
	tmp = env;
	exported_env = NULL;
	while (tmp && ++len)
		tmp = tmp->next;
	exported_env = malloc(sizeof(char *) * len++);
	add(&g_tools.garbage, export_env);
	while (env)
	{
		exported_env[i++] = env->value;
		env = env->next;
	}
	exported_env[i] = NULL;
	return (exported_env);
}

char *get_path(void)
{
	t_env *env;
	char *splited_path;

	env = g_tools.g_env;

	while (env)
	{
		if (strstr(env->variable, "PATH"))
		{
			splited_path = strstr(env->value, "=") + 1;
			return (splited_path);
		}
		env = env->next;
	}

	return (NULL);
}