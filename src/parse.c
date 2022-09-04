/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:58:58 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/04 23:36:17 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_ignore_sign(char *str)
{
	while (*str == '$')
		str++;
	return (str);
}

int	open_herdoc(int type, char *value, int id)
{
	char	*line;
	char	*buff;
	int		fd;

	buff = ft_strdup("");
	line = NULL;
	printf("%s\n", value);
	if (type == HEREDOC)
	{
		while (1)
		{
			line = readline("> ");
			add(&g_tools.garbage, line);
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
	}
	return (1);
}

void	push_red(t_red **red, t_node *t)
{
	static int	id;

	while (t)
	{
		if (t->type == REDIN || t->type == REDOUT \
				|| t->type == APPEND || t->type == HEREDOC)
		{
			if (t->next->type == 1)
			{
				id++;
				pushback_red(red, t->type, ft_strdup(t->next->next->val), id);
				open_herdoc(t->type, t->next->next->val, id);
			}
			else
			{
				id++;
				pushback_red(red, t->type, ft_strdup(t->next->val), id);
				open_herdoc(t->type, t->next->val, id);
			}
			t = t->next;
		}
		t = t->next;
	}
}

static void	push_cmd(t_cmd **cmd, t_node *t)
{
	t_red	*red;
	char	*str;
	char	**str2;

	str = ft_strdup("");
	red = NULL;
	push_red(&red, t);
	while (t)
	{
		if (t->type == WSPACE && t->next == NULL)
			break ;
		else if (t->type != REDIN && t->type != REDOUT \
				&& t->type != APPEND && t->type != HEREDOC)
			str = ft_strjoin(str, t->val);
		else
		{
			if (t->next->type == 1)
				t = t->next;
			t = t->next;
		}
		t = t->next;
	}
	str2 = ft_split(str, '\t');
	pushback_cmd(cmd, str2, red);
}

t_cmd	*parse(t_node *list)
{
	t_node	*tmp;
	t_cmd	*cmd;
	t_node	*t;

	cmd = NULL;
	tmp = list;
	t = NULL;
	while (tmp)
	{
		while (tmp->type != PIPE && tmp->next != NULL)
		{
			pushback(&t, tmp->type, tmp->val);
			tmp = tmp->next;
		}
		if (tmp->next == NULL)
			pushback(&t, tmp->type, tmp->val);
		push_cmd(&cmd, t);
		clear_list(&t);
		tmp = tmp->next;
	}
	clear_list(&tmp);
	clear_list(&t);
	return (cmd);
}
