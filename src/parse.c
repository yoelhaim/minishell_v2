/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:58:58 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/19 09:31:15 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printafternember(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar_fd(str[i], 1);
	ft_putchar_fd('\n', 1);
}

static void	check_in_env(char *str, char *str2)
{
	t_env	*env;

	env = g_tools.g_env;
	if ((str[0] >= '0' && str[0] <= '9') && !str2)
	{
		ft_putendl_fd("", 1);
		return ;
	}
	while (env)
	{
		if (!ft_strcmp(str, env->variable))
		{
			printf("%s\n", strstr(env->value, "=") + 1);
			break ;
		}
		env = env->next;
	}
	if (str2)
		printafternember(str2);
}

static int	open_herdoc(int type, char *value)
{
	char	*line;

	line = NULL;
	if (type == HEREDOC)
	{
		while (1)
		{
			line = readline("> ");
			if (!line || !ft_strcmp(line, value))
				break ;
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
		if (t->type == 9)
		{
			if (t->next)
				check_in_env(t->val, t->next->val);
			else
				check_in_env(t->val, NULL);
		}
		else if (t->type == WSPACE && t->next == NULL)
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
	free(str);
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
