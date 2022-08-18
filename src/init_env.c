/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:49:00 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/16 02:22:30 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	intail_env(char **data)
{
	int	i;

	i = 0;
	while (data[i])
		i++;
	g_data.env = (char **)malloc(sizeof(char *) * i);
	i = -1;
	while (data[++i])
	{
		g_data.env[i] = data[i];
	}
}
