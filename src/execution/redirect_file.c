/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 20:33:22 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/25 20:30:59 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_red_in(char *str)
{

int fd;

	fd =  open(str,  O_RDWR | 0 , 0777);
	if(fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", str);
		return ;
	}
	close(fd);
}

void ft_red_out(char *str)
{
	int fd;

	fd =  open(str, O_CREAT | O_RDWR| 0 , 0777);
	ft_putstr_fd("hello", fd);
	printf("%d\n", fd);
	close(fd);
}

void ft_red_append(char *str)
{
	int fd;

	fd =  open(str, O_CREAT | O_RDWR| O_APPEND | 0 , 0777);
	ft_putstr_fd("xx\n", fd);
	printf("%d\n", fd);
	close(fd);
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
		ft_red_out(red->filename);
	if(red->type == APPEND)
		ft_red_append(red->filename);
	if(red->type == HEREDOC)
		ft_red_in(".herdoc");
		red = red->next;
	}
	
}