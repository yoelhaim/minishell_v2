/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:16:51 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/26 22:14:12 by akadi            ###   ########.fr       */
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
	// while (*spl)
	// 	{
			
	// 		free(*spl);
	// 		spl++;
	// 	}
}
