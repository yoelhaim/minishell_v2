/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:51:02 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/19 09:18:23 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_ws(char *line)
{
	int	i;
	int	r;

	r = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 32 || (line[i] >= 9 && line[i] <= 15))
			r++;
	}
	if (r == i)
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*check_is_ws(t_node **list, char *line)
{
	int	r;

	r = 0;
	(void)list;
	while (*line && ft_strchr(" \t\r\n\v\f", *line))
	{
		line++;
		r++;
	}
	if (r != 0)
		pushback(list, WSPACE, "\t");
	return (line);
}

char	*check_is_pipe(t_node **list, char *line)
{
	if (*line == '|')
		pushback(list, PIPE, "|");
	return (line);
}

int	check_folder(char *name)
{
	DIR	*dirs;

	errno = 0;
	dirs = opendir(name);
	if (!name)
		return (ERROR_RETURN);
	if ((dirs) == NULL)
	{
		if (errno == 13)
			printf("permission denied\n");
		if (errno == ENOENT)
			printf("Directory does not exist\n");
		if (errno == ENOTDIR)
			printf("is not a directory\n");
		return (ERROR_RETURN);
	}
	return (1);
}
