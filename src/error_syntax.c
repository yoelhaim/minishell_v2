/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:48:30 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/29 13:48:55 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void test1(t_node **data)
{
	t_node *tmp = *data;
	while (tmp)
	{
		printf("---------------\n");
		printf("---value %s\n", tmp->val);
		printf("---type %d\n", tmp->type);
		printf("------------------\n");
		
	tmp = tmp->next;
	}
	
}

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
			checkerr_red(buff, tmp_red, str);
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
				while (line->type == WSPACE)
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
// 	t_node *tmp;
// 	//t_node *helper;

// 	tmp = list;
// 	//helper = list;
// 	while (tmp->next)
// 	{
// 		if(tmp->next == NULL)
// 		{
// 			if(tmp->type == WSPACE)
// 			{
// 				free(tmp->next);
// 				tmp->next = NULL;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
	
// test1(&tmp);
// 	return  1;
	if (valid_pipe(list) == ERROR_RETURN \
	|| check_after_red(list) == ERROR_RETURN)
		return (ERROR_RETURN);
	return (1);
}
