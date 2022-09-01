/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:48:30 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/01 15:54:39 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_after_red(t_node *list)
{
	t_node	*str;
	char	*buff;
	int		tmp_red;

	str = list;
	while (str)
	{
		buff = str->val;
		tmp_red = str->type;
		if (str->next != NULL)
		{
			if (checkerr_red(buff, tmp_red, str) == ERROR_RETURN)
				return (ERROR_RETURN);
		}
		else if ((!strcmp(buff, "<") || !strcmp(buff, "<<") \
		|| !strcmp(buff, ">") || !strcmp(buff, ">>")) \
		&& (tmp_red >= 3 && tmp_red <= 6))
			return (ft_putstr_fd(create_err(NL_ERROR_MESSSAGE \
					, NULL, "\n"), 2), ERROR_RETURN);
		str = str->next;
	}
	return (1);
}

int	check_pipe_is_end(t_node *list)
{
	t_node	*line;
	char	*tmp;
	int		type_tmp;

	line = list;
	while (line)
	{
			tmp = line->val;
			type_tmp = line->type;
		line = line->next;
	}
	if (tmp[0] == '|' && type_tmp == 2)
		return (ft_putstr_fd(create_err(TOKEN_ERR, \
		tmp, "\n"), 2), ERROR_RETURN);
	return (1);
}

static int	valid_pipe(t_node *list)
{
	t_node	*line;

	line = list;
	if (line->type == PIPE)
		return (ft_putstr_fd(create_err(TOKEN_ERR, \
		line->val, "\n"), 2), ERROR_RETURN);
	while (line)
	{
		if (line->type == PIPE)
		{
			line = line->next;
			if ((line))
			{
				while (line->type == WSPACE && line->next != NULL)
					line = line->next;
				if (line->type == PIPE)
					return (ft_putstr_fd(create_err(TOKEN_ERR, \
					line->val, "\n"), 2), ERROR_RETURN);
			}
		}
		else
			line = line->next;
	}
	return (check_pipe_is_end(list));
}

int	syntax_error(t_node *list)
{
	t_node	*red;

	red = list;
	while (red)
	{
		if (red->type == HEREDOC)
		{
			if (red->next->type == 1)
				open_herdoc(red->type, red->next->next->val);
			else
				open_herdoc(red->type, red->next->val);
		}
		red = red->next;
	}
	
	if (valid_pipe(list) == ERROR_RETURN \
	|| check_after_red(list) == ERROR_RETURN)
		return (ERROR_RETURN);
	return (1);
}
