/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:12 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/27 17:18:56 by akadi            ###   ########.fr       */
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
		printf(MOVE_UP_RIGHRT "exitddd\n");
		exit(1);
	}
	if (read_line && read_line[0])
		add_history(read_line);
	return (read_line);
}
