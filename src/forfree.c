/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:06:12 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/17 17:17:21 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//  void	ft_freearr(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	if (!arr)
// 		return ;
// 	while (arr[i])
// 		free(arr[i++]);
// 	free(arr);
// }

void add(t_node_free **garbage, void *pointer)
{
    t_node_free *node;

    node = malloc(sizeof(t_node_free));
    node->pointer = pointer;
    node->next = *garbage;
    *garbage = node;
}

void free_all(t_node_free *garbage)
{
    void *tmp;

    tmp = NULL;
    while (garbage)
    {
        free(garbage->pointer);
        tmp = garbage;
        garbage = garbage->next;
        free(tmp);
    }
}