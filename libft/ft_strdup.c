/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:55:33 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 15:23:47 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;
	size_t	len_str;

	i = 0;
	len_str = ft_strlen(s1) + 1;
	dup = malloc(len_str);
	add(&g_tools.garbage, dup);
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
