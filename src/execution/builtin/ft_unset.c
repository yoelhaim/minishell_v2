/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:06:14 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 17:28:13 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*remove_to_env(char **cmd, t_env *list)
{
	t_env	*tmp;
	t_env	*prev;

	list = g_tools.g_env;
	tmp = g_tools.g_env;
	prev = g_tools.g_env;
	tmp = tmp->next;
	while (*(cmd))
	{
		tmp = list->next;
		prev = list;
		while (tmp)
		{
			if (!ft_strcmp(tmp->variable, *cmd))
			{
				prev->next = tmp->next;
				break ;
			}
			tmp = tmp->next;
			prev = prev->next;
		}
		cmd++;
	}
	add(&g_tools.garbage, tmp);
	return (list);
}

t_env	*ft_unset(char **cmd)
{
	t_env	*list;
	t_env	*tmp;
	t_env	*prev;

	list = g_tools.g_env;
	tmp = g_tools.g_env;
	prev = g_tools.g_env;
	if (!list)
		return (NULL);
	else
	{
		tmp = tmp->next;
		if (!ft_strcmp(prev->variable, cmd[1]))
		{
			list = list->next;
			return (list);
		}
	}
	cmd++;
	if (!*cmd)
		return (list);
	remove_to_env(cmd, list);
	return (list);
}
