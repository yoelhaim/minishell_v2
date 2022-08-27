/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:33:22 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/27 23:19:15 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_n_of_red(t_red *red)
{
	t_red	*tmp;
	int		i;

	i = 0;
	tmp = red;
	while (red)
	{
		i++;
		red = red->next ;
	}
	return (i);
}

int	check_red(int type, char *namefile, int *status)
{
	if (type == REDOUT)
		open_redout(namefile);
	else if (type == APPEND)
		open_append(namefile);
	else if (type == REDIN)
	{
		if (open_in(namefile, status) == ERROR_RETURN)
			return (ERROR_RETURN);
	}
	return (1);
}

int	check_redirecrt(t_red *red, int *status)
{
	int		len;
	t_red	*tmp;

	g_tools.r_in = 0;
	g_tools.w_out = 1;
	len = check_n_of_red(red);
	tmp = red;
	if (len > 0)
	{
		while (red)
		{
			if (check_red(red->type, red->filename, status) == ERROR_RETURN)
				return (ERROR_RETURN);
			red = red->next ;
		}
	}
	return (1);
}
