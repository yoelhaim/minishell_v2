/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:33:22 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/19 22:00:05 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_red_in(char *str)
{
	printf("%s\n", str);
}

void ft_red_out(char *str)
{
	printf("%s\n", str);
}

void check_redirecrt(t_red *reds)
{

	t_red  *red;
	red = reds;
	while(red)
	{
	if(red->type == REDIN)
		ft_red_in(red->filename);
	if(red->type == REDOUT)
		ft_red_in(red->filename);
		red = red->next;
	}
	
	
}