/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:16:51 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 16:06:23 by akadi            ###   ########.fr       */
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
		if (ft_strcmp(*spl, "OLDPWD"))
			pushback_env(&g_tools.g_env, *spl, data[i]);
	}
}
