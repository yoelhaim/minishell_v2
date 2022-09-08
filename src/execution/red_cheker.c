/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_cheker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:00:23 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/08 16:44:32 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_error_fd(void)
{
	ft_putstr_fd(create_err("No such file or directory\n", NULL, NULL), 2);
}

void	open_redout(char *filename, int *status)
{
	g_tools.w_out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (g_tools.w_out == -1)
	{
		handle_error_fd();
		return ;
	}
	*status = 0;
	dup2(g_tools.w_out, 1);
	close(g_tools.w_out);
}

void	open_append(char *filename)
{
	g_tools.w_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (g_tools.w_out == -1)
	{
		dup2(g_tools.dup_out, 1);
		close(g_tools.w_out);
		handle_error_fd();
		return ;
	}
	dup2(g_tools.w_out, 1);
	close(g_tools.w_out);
}

int	open_in(char *filename, int *status)
{
	(void) status;
	g_tools.r_in = open(filename, O_RDONLY, 0644);
	if (g_tools.r_in == -1)
	{
		handle_error_fd();
		return (ERROR_RETURN);
	}
	*status = 0;
	dup2(g_tools.r_in, 0);
	close(g_tools.r_in);
	return (1);
}

int	open_herdoc_file(char *filename, int *status)
{
	(void) status;
	g_tools.r_in = open(filename, O_RDONLY, 0644);
	if (g_tools.r_in == -1)
	{
		handle_error_fd();
		return (ERROR_RETURN);
	}
	unlink(filename);
	*status = 0;
	dup2(g_tools.r_in, 0);
	close(g_tools.r_in);
	return (1);
}
