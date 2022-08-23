/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 09:19:50 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/23 14:12:31 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	check_expand_status(char **value)
{
	*value = ft_itoa(g_tools.status_sign);
}
void	check_expand_dollar(char **value)
{
	char	*val;
	t_env	*env;

	val = *value;
	env = g_tools.g_env;


	while (env)
	{
		if (!ft_strcmp(env->variable, val))
		{
			*value = strstr(env->value, "=") + 1;
			break ;
		}
		else
		{
			if (val[0] == '0' && val[1] == '\0')
				*value = "minishell";
			else if (val[0] >= '1' && val[0] <= '9' && val[1] == '\0')
				*value = "\0";
			else if (val[0] >= '1' && val[0] <= '9' && val[1] != '\0')
				*value = "\0";
			else
				*value = "\0";
		}

		env = env->next;
	}

}

void	expander(t_node **list)
{
	t_node	*cmd;

	cmd = *list;
	while (cmd)
	{
		if (cmd->type == SIGN)
			check_expand_dollar(&cmd->val);
		else if (cmd->type == EXIT_STATUS)
			check_expand_status(&cmd->val);
		cmd = cmd->next;
	}
}
