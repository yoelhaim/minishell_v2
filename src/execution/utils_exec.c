/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:34:27 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/23 12:10:10 by yoelhaim         ###   ########.fr       */
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

char	*get_path(void)
{
	t_env	*env;

	env = g_tools.g_env;
	while (env)
	{
		if (strstr(env->variable, "PATH"))
			return (strstr(env->value, "=") + 1);
		env = env->next;
	}
	return (NULL);
}

int	size_word(char **cmd)
{
	int	i;

	i = 0;
	if(!*cmd)
		return (ERROR_RETURN);
	while(cmd[i])
		i++;
	return(i);
}

int check_cmd_valid(char *cmd)
{
	if(cmd[0] >= '0' && cmd[0] <= '9')
		return (printf("bash: export: `%s': not a valid identifier\n",cmd),1);
	
	return(ERROR_RETURN);
}

void	check_exported_append(char **splited_value, char **cmd, int *append)
{
	int	i;

	i = 0;
	char *str;
	if (strstr(*cmd, "+="))
	{
		while (splited_value[0][i])
			i++;
		str = malloc(sizeof(char) * i);
		i = -1;
		while (splited_value[0][++i])
			str[i] = splited_value[0][i];
		str[i -1] = 0;
		splited_value[0] = str;
		*cmd = ft_strjoin(splited_value[0], "=");
		if (splited_value[1])
			*cmd = ft_strjoin(*cmd, splited_value[1]);
		*append = 1;
	}
}

