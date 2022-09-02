/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 09:19:50 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/02 00:57:34 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_expand_status(char **value)
{
	*value = ft_itoa(g_tools.status_sign);
}

int	push_sym_whit_sign(t_node **list, char line)
{
	char	*symb;
	char	*str;

	symb = ft_strdup("\"%'()*+,-./:\\^`|~");
	str = malloc(2);
	add(&g_tools.garbage, str);
	str[0] = line;
	str[1] = 0;
	while (*symb)
	{
		if (line == *symb)
			return (pushback(list, WORD, ft_strjoin("$", str)), 1);
		symb++;
	}
	return (ERROR_RETURN);
}

void	ft_update(char *val, char ***value)
{
	if (val[0] == '0' && val[1] == '\0')
		**value = ft_strdup("minishell");
	else if (val[0] >= '1' && val[0] <= '9' && val[1] == '\0')
		**value = ft_strdup("\0");
	else if (val[0] >= '1' && val[0] <= '9' && val[1] != '\0')
		**value = ft_strdup("\0");
	else
		**value = ft_strdup("\0");
}

void	check_expand_dollar(char **value, int i)
{
	char	*val;
	t_env	*env;

	val = *value;
	env = g_tools.g_env;
	while (env)
	{
		if (!ft_strcmp(env->variable, val))
		{
			*value = ft_strstr(env->value, "=") + 1;
			break ;
		}
		else
			ft_update(val, &value);
		env = env->next;
		i++;
	}
	if (i == 0)
		*value = "\0";
}

void	expander(t_node **list)
{
	t_node	*cmd;
	int		i;

	i = 0;
	cmd = *list;
	while (cmd)
	{
		if (cmd->type == SIGN)
			check_expand_dollar(&cmd->val, i);
		else if (cmd->type == EXIT_STATUS)
			check_expand_status(&cmd->val);
		cmd = cmd->next;
	}
}
