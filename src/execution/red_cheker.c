/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_cheker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:00:23 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 22:46:31 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_redout(char *filename)
{
	g_tools.w_out = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(g_tools.w_out, 1);
	close(g_tools.w_out);
}

void	open_append(char *filename)
{
	g_tools.w_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(g_tools.w_out, 1);
	close(g_tools.w_out);
}

int	open_in(char *filename, int *status)
{
	g_tools.r_in = open(filename, O_RDONLY, 0644);
	if (g_tools.r_in == -1)
	{
		*status = 0;
		dup2(g_tools.r_in, 0);
		close(g_tools.r_in);
		ft_putstr_fd("No such file or directory\n", 2);
		return (ERROR_RETURN);
	}
	*status = 0;
	dup2(g_tools.r_in, 0);
	close(g_tools.r_in);
	return (1);
}

int	open_herdoc_file(int *status, t_red *cmd)
{
	static int	len;

	(void)cmd;
	len++;
	g_tools.r_in = open(".herdoc", O_RDONLY, 0644);
	if (g_tools.r_in == -1)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (ERROR_RETURN);
	}
	if (len == 0)
		unlink(".herdoc");
	*status = 0;
	dup2(g_tools.r_in, 0);
	close(g_tools.r_in);
	return (1);
}
