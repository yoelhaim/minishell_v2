/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 01:27:47 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/02 20:58:54 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_is_pipe(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->type == PIPE)
			i++;
		list = list->next;
	}
	return (i);
}

void	ft_print_ign_bs(char *cmd, char *buff)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\\')
			buff[cont++] = cmd[i];
		else if (cmd[i++] == '\\')
			buff[cont++] = cmd[i];
		i++;
	}
}

char	*remove_back_slash(char *cmd)
{
	int		i;
	int		cont;
	char	*buff;

	i = 0;
	cont = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\\')
			cont++;
		i++;
		if (cmd[i] == '\\')
			cont++;
	}
	buff = malloc(cont + 1);
	add(&g_tools.garbage, buff);
	ft_print_ign_bs(cmd, buff);
	buff[cont] = 0;
	return (buff);
}

// char	**rm_ba(char **cmd)
// {
// 	char	**buff;
// 	int		i;

// 	i = 0;
// 	while (cmd[i] != (void *)0)
// 		i++;
// 	buff = malloc(i + 1);
// 	add(&g_tools.garbage, buff);
// 	i = 0;
// 	while (cmd[i] != (void *)0)
// 	{
// 		buff[i] = remove_back_slash(cmd[i]);
// 		i++;
// 	}
// 	buff[i] = 0;
// 	free(cmd);
// 	return (buff);
// }
