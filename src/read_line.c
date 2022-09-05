/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:12 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/05 21:00:51 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_herdoc(int id, char *value)
{
	char	*line;
	char	*buff;
	int		fd;

	buff = ft_strdup("");
	line = NULL;
	printf("val => %s\n", value);
	signal(SIGINT, handler_herdock);
	while (1)
	{
		line = readline("> ");
		add(&g_tools.garbage, line);
		printf("line => %s\n", ft_ignore_sign(line));
		if (!line || !ft_strcmp(ft_ignore_sign(line) \
					, ft_ignore_sign(value)))
			break ;
		else
			buff = ft_strjoin(buff, ft_strjoin(line, "\n"));
	}
	fd = open (ft_strjoin("/tmp/.herdoc", ft_itoa(id)), \
			O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_putstr_fd(buff, fd);
	close(fd);
	exit(0);
}

void	handler(int sig)
{
	(void) sig;
	rl_catch_signals = 0;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handler_herdock(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	exit(1);
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
	if (!buff)
		return (NULL);
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
	add(&g_tools.garbage, read_line);
	if (!read_line)
	{
		printf(MOVE_UP_RIGHRT "exit\n");
		exit(1);
	}
	if (read_line && read_line[0])
		add_history(read_line);
	return (return_line(ft_strtrim(read_line, " ")));
}
