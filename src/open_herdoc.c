/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:04:32 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/08 16:45:06 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_value(char *value)
{
	char	*buff;
	int		i;

	i = 0;
	while (value[i] && value[i] != ' ')
		i++;
	buff = malloc(i + 1);
	add(&g_tools.garbage, buff);
	i = 0;
	while (value[i] && value[i] != ' ')
	{
		buff[i] = value[i];
		i++;
	}
	buff[i] = 0;
	return (buff);
}

char	*get_filename(char *filename)
{
	if (check__is_exits(filename))
		return (get_filename(ft_strjoin(filename, "_c")));
	return (filename);
}

void	child_herdoc_now(char ***value, int *type)
{
	char	*line;
	char	*buff;
	char	*filename;
	int		fd;

	buff = ft_strdup("");
	line = NULL;
	**value = return_value(ft_strtrim(**value, " "));
	while (1)
	{
		line = readline("> ");
		if (*type == SIGN)
			line = ft_strtrim(line, "$");
		add(&g_tools.garbage, line);
		if (!line || !ft_strcmp(**value, line))
			break ;
		else
			buff = ft_strjoin(buff, ft_strjoin(line, "\n"));
	}
	filename = get_filename(ft_strjoin("/tmp/.herdooc", ft_itoa(g_tools.n_h)));
	**value = filename;
	fd = open (**value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	*type = 11;
	ft_putstr_fd(buff, fd);
	close(fd);
}

int	open_herdoc_now(char **value, int *type)
{
	static int	id;

	id++;
	g_tools.n_h = id;
	child_herdoc_now(&value, type);
	return (1);
}

void	check_is_herdoc(t_node **list)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (tmp->next->type == 1 && tmp->next != NULL)
				open_herdoc_now(&tmp->next->next->val, &tmp->next->next->type);
			else
				open_herdoc_now(&tmp->next->val, &tmp->next->type);
		}
		tmp = tmp->next;
	}
}
