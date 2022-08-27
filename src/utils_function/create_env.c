/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:16:51 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/27 21:08:33 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	create_env(char *data[])
{
	int		i;
	char	**spl;

	i = -1;
	while (data[++i])
	{
		spl = ft_split(data[i], '=');
		pushback_env(&g_tools.g_env, *spl, data[i]);
	}
}
