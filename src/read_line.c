/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:12 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 15:59:37 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	(void) sig;
	rl_catch_signals = 0;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

char	*return_line(char *line)
{
	int		len;
	char	*buff;
	int		i;

	i = -1;
	len = ft_strlen(line) - 1;
	while (line[len] == ' ')
		len--;
	buff = malloc(sizeof(char) * (len + 1));
	add(&g_tools.garbage, buff);
	while (++i <= len)
		buff[i] = line[i];
	buff[i] = '\0';
	free(line);
	return (buff);
}

char	*read_line(void)
{
	char	*read_line;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	read_line = readline("miniShell$ ");
	if (!read_line)
	{
		printf(MOVE_UP_RIGHRT "exit\n");
		exit(1);
	}
	if (read_line && read_line[0])
		add_history(read_line);
	return (return_line(read_line));
}
