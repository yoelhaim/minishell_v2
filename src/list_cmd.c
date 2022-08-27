/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:28:56 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/27 21:10:26 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*new_node_cmd(char **arg, t_red *red)
{
	t_cmd	*newnode;

	newnode = (t_cmd *)malloc(sizeof(t_cmd));
	add(&g_tools.garbage, new_node);
	if (newnode != NULL)
	{
		newnode->cmnd = arg;
		newnode->red = red;
		newnode->r_in = 0;
		newnode->w_out = 1;
		newnode->next = NULL;
	}
	return (newnode);
}

void	pushback_cmd(t_cmd **lst, char **arg, t_red *red)
{
	t_cmd	*head;
	t_cmd	*new;

	new = new_node_cmd(arg, red);
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

t_cmd	*clear_list_cmd(t_cmd **lst)
{
	t_cmd	*forfree;

	while ((*lst))
	{
		forfree = (*lst);
		(*lst) = (*lst)->next;
		free(forfree);
	}
	return (NULL);
}

int	size_of_cmd(t_cmd **list)
{
	t_cmd	*cmd;
	int		i;

	cmd = *list;
	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
