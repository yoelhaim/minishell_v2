/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_lixer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:25:31 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/02 22:04:06 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*middle_quets_s(t_node **list, char *line, char quot, int i)
{
	char	*buff;

	buff = 0;
	if (i == 0 && *(line + 1) == '\0')
	{
		pushback(list, WORD, " ");
		return (" ");
	}
	buff = malloc(sizeof(char) * (i + 1));
	add(&g_tools.garbage, buff);
	if (!buff)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != quot)
	{
		buff[i] = line[i];
		i++;
	}
	buff[i] = 0;
	pushback(list, WORD, buff);
	return (NULL);
}

void	pushstr_quets(char *buff, t_node **list, char quot)
{
	while (*buff != 0)
	{
		buff = check_is_wd(list, buff, "$");
		if (quot == '"')
			buff = check_is_sign(list, buff);
		buff++;
	}
}

char	*middle_quets(t_node **list, char *line, char quot, int i)
{
	char	*buff;

	buff = ft_strdup("");
	buff = malloc(sizeof(char) * (i + 1));
	add(&g_tools.garbage, buff);
	if (!buff)
		return (NULL);
	if (i == 0 && *(line + 1) == '\0')
	{
		pushback(list, WORD, " ");
		return (" ");
	}
	i = 0;
	while (line[i] && line[i] != quot)
	{
		buff[i] = line[i];
		i++;
	}
	buff[i] = 0;
	pushstr_quets(buff, list, quot);
	return (NULL);
}

char	*check_is_red(t_node **list, char *line)
{
	if (*line == '<' && line[1] == '<')
	{
		pushback(list, HEREDOC, "<<");
		line++;
	}
	else if (*line == '<')
		pushback(list, REDIN, "<");
	else if (*line == '>' && line[1] == '>')
	{
		pushback(list, APPEND, ">>");
		line++;
	}
	else if (*line == '>')
		pushback(list, REDOUT, ">");
	return (line);
}
