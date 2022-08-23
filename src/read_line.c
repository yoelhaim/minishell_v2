/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:12 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/23 12:54:21 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	struct termios	t;

	(void)sig;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

char	*read_line(void)
{
	char	*read_line;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	read_line = readline("miniShell$ ");
	if (!read_line)
	{
		write(1, "exit\n", 5);
		exit(1);
	}
	if (read_line && read_line[0])
		add_history(read_line);
	return (read_line);
}
