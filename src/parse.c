/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:58:58 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/25 00:00:55 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	open_herdoc(int type, char *value)
{
	char	*line;
	char	*buff;
	
	buff = NULL;
	line = NULL;
	if (type == HEREDOC)
	{
		while (1)
		{
		line = readline("> ");
		if (!line || !ft_strcmp(line, value))
				break ;
		else
		{
		int fd = open(".herdoc", O_RDWR|O_CREAT, 0666);
		printf("=>%d\n", fd);
		char *l = line;
		if(buff != NULL)
	     {	
		buff = malloc(ft_strlen(l) + ft_strlen(buff));
		write(fd, buff, ft_strlen(buff) + ft_strlen(l) );
		}
		buff = ft_strjoin(buff, l);
		// read(fd, buff,ft_strlen(buff)  +1 );
		
		
		printf("len => %zu\n str %s\n", ft_strlen(l), buff);
		}
		}
		
	}
	return (1);
}

static void	push_red(t_red **red, t_node *t)
{
	while (t)
	{
		if (t->type == REDIN || t->type == REDOUT \
		|| t->type == APPEND || t->type == HEREDOC)
		{
			if (t->next->type == 1)
			{
				pushback_red(red, t->type, ft_strdup(t->next->next->val));
				open_herdoc(t->type, ft_strdup(t->next->next->val));
			}
			else
			{
				pushback_red(red, t->type, t->next->val);
				open_herdoc(t->type, t->next->val);
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

	str = "";
	red = NULL;
	push_red(&red, t);
	while (t)
	{
		// if (t->type == 9)
		// {
		// 	if (t->next)
		// 		check_in_env(t->val, t->next->val);
		// 	else
		// 		check_in_env(t->val, NULL);
		// }
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
	// free(str);
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
	return (cmd);
}
