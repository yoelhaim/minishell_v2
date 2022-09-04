/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:06:12 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 20:42:31 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add(t_node_free **garbage, void *pointer)
{
	t_node_free	*node;

	node = malloc(sizeof(t_node_free));
	if (!node)
		return ;
	node->pointer = pointer;
	node->next = *garbage;
	*garbage = node;
}

void	free_all(t_node_free *garbage)
{
	void	*tmp;

	tmp = NULL;
	while (garbage)
	{
		free(garbage->pointer);
		tmp = garbage;
		garbage = garbage->next;
		free(tmp);
	}
}
