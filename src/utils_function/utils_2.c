/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:49:23 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 13:06:33 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_err(char *firs_s, char *midl_s, char *last_s)
{
	char *str;

	str = NULL;
	if (!firs_s)
		return (NULL);
	if (midl_s && last_s)
		str = ft_strjoin(firs_s, ft_strjoin(midl_s, last_s));
	else if (!midl_s && last_s)
		str = ft_strjoin(firs_s, last_s);
	else
		str = "error ";
	
	return (str);
}