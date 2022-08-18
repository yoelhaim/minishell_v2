/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:07:05 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/17 01:42:43 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *new_node(int type, char *val)
{
	t_node *newnode;

	newnode = (t_node *)malloc(sizeof(t_node));
	add(&g_tools.garbage, new_node);
	if (newnode != NULL)
	{
		newnode->type = type;
		newnode->val = val;
		newnode->next = NULL;
	}
	return (newnode);
}

void pushback(t_node **lst, int type, char *val)
{
	t_node *head;
	t_node *new;

	new = new_node(type, val);
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

t_node *clear_list(t_node **lst)
{
	t_node *forfree;

	while ((*lst))
	{
		forfree = (*lst);
		(*lst) = (*lst)->next;

		free(forfree);
	}
	return (NULL);
}
