/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:48:30 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/25 00:03:09 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_after_red(t_node *list)
{
	t_node	*str;
	char	*buff;

	str = list;
	while (str)
	{
		buff = str->val;
		if (str->next != NULL)
		{
			if (!strcmp(buff, "<") || !strcmp(buff, "<<") \
			|| !strcmp(buff, ">") || !strcmp(buff, ">>"))
			{
				if (str->next->type == 1 && str->next->next != NULL)
					str = str->next;
				if (str->next->type != 11)
					return (printf("%s\n", NL_ERROR_MESSSAGE), ERROR_RETURN);
			}
		}
		else if ((!strcmp(buff, "<") || !strcmp(buff, "<<") \
		|| !strcmp(buff, ">") || !strcmp(buff, ">>")))
			return (printf("%s\n", NL_ERROR_MESSSAGE), ERROR_RETURN);
		str = str->next;
	}
	return (1);
}

int	check_pipe_is_end(t_node *list)
{
	t_node	*line;
	char	*tmp;

	line = list;
	while (line)
	{
		tmp = line->val;
		line = line->next;
	}
	if (tmp[0] == '|')
		return (printf("%s %s' \n", TOKEN_ERR, tmp), ERROR_RETURN);
	return (1);
}

static int	valid_pipe(t_node *list)
{
	t_node	*line;

	line = list;
	if (line->type == PIPE)
		return (printf("%s %s' \n", TOKEN_ERR, line->val), ERROR_RETURN);
	while (line)
	{
		if (line->type == PIPE)
		{
			line = line->next;
			if ((line))
			{
				while (line->type == WSPACE)
				line = line->next;
				if (line->type == PIPE)
					return (printf("%s %s\n", \
					TOKEN_ERR, line->val), ERROR_RETURN);
			}
		}
		else
			line = line->next;
	}
	return (check_pipe_is_end(list));
}

int	syntax_error(t_node *list)
{
	if (valid_pipe(list) == ERROR_RETURN \
	|| check_after_red(list) == ERROR_RETURN)
		return (ERROR_RETURN);
	return (1);
}
