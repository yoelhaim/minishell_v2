/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:00:14 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/21 23:24:07 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*new_node_env(char *variable, char *val)
{
	t_env	*newnode;

	newnode = (t_env *)malloc(sizeof(t_env));
	if (newnode != NULL)
	{
		newnode->variable = variable;
		newnode->value = val;
		newnode->next = NULL;
	}
	return (newnode);
}

void	pushback_env(t_env **lst, char *variable, char *val)
{
	t_env	*head;
	t_env	*new;

	new = new_node_env(variable, val);
	if (!*lst)
		*lst = new;
	else
	{
		head = *lst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_env	*clear_list_env(t_env **lst)
{
	t_env	*forfree;

	while ((*lst))
	{
		forfree = (*lst);
		(*lst) = (*lst)->next;
		free(forfree);
	}
	return (NULL);
}
