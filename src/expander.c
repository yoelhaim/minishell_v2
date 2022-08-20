/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 09:19:50 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/20 11:33:05 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_expand_dollar(char **value)
{
	char	*val;
	t_env	*env;

	val = *value;
	env = g_tools.g_env;
	if (val[0] == '0' && val[1] == '\0')
		*value = "minishell";
	if (val[0] >= '1' && val[0] <= '9' && val[1] == '\0')
		*value = "\0";
	if (val[0] >= '1' && val[0] <= '9' && val[1] != '\0')
		*value = "\0";
	else
	{
		while (env)
		{
			if (!ft_strcmp(env->variable, val))
			{
				*value = strstr(env->value, "=") + 1;
				break ;
			}
			env = env->next;
		}
	}
}

void	expander(t_node **list)
{
	t_node	*cmd;

	cmd = *list;
	while (cmd)
	{
		if (cmd->type == 9)
			check_expand_dollar(&cmd->val);
		cmd = cmd->next;
	}
}
