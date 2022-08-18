/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:01:09 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/17 01:43:12 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_red *new_node_red(int type, char *val)
{
	t_red *newnode;

	newnode = (t_red *)malloc(sizeof(t_red));
	add(&g_tools.garbage, new_node);
	if (newnode != NULL)
	{
		newnode->type = type;
		newnode->filename = val;
		newnode->next = NULL;
	}
	return (newnode);
}

void pushback_red(t_red **lst, int type, char *val)
{
	t_red *head;
	t_red *new;

	new = new_node_red(type, val);
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

t_red *clear_list_red(t_red **lst)
{
	t_red *forfree;

	while ((*lst))
	{
		forfree = (*lst);
		(*lst) = (*lst)->next;
		free(forfree);
	}
	return (NULL);
}
