/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:28:37 by yoelhaim          #+#    #+#             */
/*   Updated: 2021/11/13 13:14:28 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ls_new;

	ls_new = malloc(sizeof(t_list));
	if (!ls_new)
		return (NULL);
	ls_new->content = content;
	ls_new->next = NULL;
	return (ls_new);
}
