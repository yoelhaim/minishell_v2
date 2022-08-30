/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:05:02 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/30 12:58:24 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_valid_export(char **cmd)
{
	char	**str;

	str = cmd;
	while (*str)
	{
		if (!ft_strcmp(*str, "="))
			return (ERROR_RETURN);
		str++;
	}
	str = cmd;
	while (*str)
	{
		if (*str[0] == '=')
			return (ERROR_RETURN);
		str++;
	}
	return (1);
}

void	next_export(char **cmd, char **splited_value, int status, t_env *env)
{
	int	append;
	t_env	*tmp;
	static int	is_first_append;
	
	append = 0;
	while (*cmd)
	{
		*cmd = get_cmd_export(&splited_value, *cmd);
		if (*cmd == NULL)
			return ;
		check_exported_append(&splited_value, &cmd, &append);
		tmp = env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->variable, splited_value[0]))
			{
				printf("is here %s  ==  %s\n", splited_value[0], tmp->variable);
				
				if (append)
					*cmd = ft_strjoin(tmp->value, splited_value[1]);
				tmp->value = *cmd;
				status = 1;
				break ;
			}
			is_first_append = 0;
			status = 0;
			tmp = tmp->next;
		}
		if(is_first_append == 0 && append)
			ft_push_to_env(&status, &is_first_append, splited_value[0], *cmd);
		ft_push_to_env(&status, &append, splited_value[0], *cmd);
		cmd++;
		is_first_append++;
	}
}

void	printf_export(char **str)
{
	char	**export;
	int		i;
	char	*variable;

	i = 0;
	export = str;
	variable = NULL;
	while (i <= size_of_env() && export[i + 1])
	{
		if (export[i][0] > export[i + 1][0])
		{
			variable = export[i + 1];
			export[i + 1] = export[i];
			export[i] = variable;
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (export[i])
		printf("declare -x %s\n", export[i++]);
}

void	getexport(void)
{
	t_env	*env;
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	env = g_tools.g_env;
	while (env)
	{
		i++;
		env = env->next;
	}
	str = malloc(sizeof(char *) * i + 1);
	add(&g_tools.garbage, str);
	i = 0;
	env = g_tools.g_env;
	while (env)
	{
		str[i] = env->value;
		i++;
		env = env->next;
	}
	str[i] = 0;
	printf_export(str);
}

void	ft_export(char **cmd)
{
	t_env	*env;
	int		status;
	char	*splited_value;

	env = g_tools.g_env;
	status = 0;
	splited_value = NULL;
	cmd++;
	if (check_valid_export(cmd) == ERROR_RETURN)
	{
		ft_putstr_fd("minishel: export: `=': not a valid identifier\n", 2);
		return ;
	}
	if (*cmd != NULL)
		next_export(cmd, &splited_value, status, env);
	else
		getexport();
}
