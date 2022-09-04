/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:16:51 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 23:39:55 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#define _PATH_STDPATH   "/usr/bin:/bin:/usr/sbin:/sbin:"

void	add_ifn_env(void)
{
	char	path[1024];

	getcwd(path, 1024);
	pushback_env(&g_tools.g_env, "PATH", ft_strjoin("PATH=", _PATH_STDPATH));
	pushback_env(&g_tools.g_env, "SHELVL", "SHLVL=1");
	pushback_env(&g_tools.g_env, "PWD", ft_strjoin("PWD=", path));
}

void	create_env(char *data[])
{
	int		i;
	char	**spl;

	i = -1;
	if (!*data)
	{
		add_ifn_env();
		return ;
	}
	while (data[++i])
	{
		spl = ft_split(data[i], '=');
		if (ft_strcmp(*spl, "OLDPWD"))
			pushback_env(&g_tools.g_env, *spl, data[i]);
	}
}
