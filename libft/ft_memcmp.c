/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:07:48 by yoelhaim          #+#    #+#             */
/*   Updated: 2021/11/09 21:56:39 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*src1;
	char	*src2;

	src1 = (char *)s1;
	src2 = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (src1[i] != src2[i])
			return (((unsigned char *)src1)[i] - ((unsigned char *)src2)[i]);
		i++;
	}
	return (0);
}
