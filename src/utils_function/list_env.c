/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:00:14 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/08 21:00:34 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*new_node_env(char *variable, char *val)
{
	t_env	*newnode;

	newnode = (t_env *)malloc(sizeof(t_env));
	add(&g_tools.garbage, new_node);
	if (newnode != NULL)
	{
		newnode->variable = variable;
		newnode->value = val;
		newnode->next = NULL;
	}
	return (newnode);
}

void	pushback_env(t_env **lst, char *variable, char *val)
{
	t_env	*head;
	t_env	*new;

	new = new_node_env(variable, val);
	if (!*lst)
		*lst = new;
	else
	{
		head = *lst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

int	size_of_env(void)
{
	int		i;
	t_env	*env;

	env = g_tools.g_env;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*clear_list_env(t_env **lst)
{
	t_env	*forfree;

	while ((*lst))
	{
		forfree = (*lst);
		(*lst) = (*lst)->next;
		free(forfree);
	}
	return (NULL);
}

char	*check_this(t_node *list)
{
	t_node	*tmp;
	char	*buff;

	tmp = list;
	buff = ft_strdup("");
	if (tmp->type == 1)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == 1)
			break ;
		if (tmp->type == 9)
			buff = ft_strjoin(buff, ft_strjoin("$", tmp->val));
		else
			buff = ft_strjoin(buff, tmp->val);
		tmp->val = ft_strdup("\0");
		tmp->type = 1;
		tmp = tmp->next;
	}
	return (buff);
}
