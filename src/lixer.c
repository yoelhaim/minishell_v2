/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:54:42 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/08 11:57:06 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_is_wd(t_node **list, char *line, char *sc)
{
	char	*buff;
	int		i;

	i = 0;
	buff = ft_strdup("");
	while (!ft_strchr(sc, line[i]))
		i++;
	buff = malloc(sizeof(char) * i);
	if (!buff)
		return (NULL);
	add(&g_tools.garbage, buff);
	i = 0;
	while (*line && !ft_strchr(sc, *line))
		buff[i++] = *line++;
	if (i != 0)
	{
		buff[i] = 0;
		if (ft_strlen(sc) == 12 || ft_strlen(sc) == 1)
			pushback(list, WORD, buff);
		else
			pushback(list, SIGN, buff);
		return (line - 1);
	}
	return (line);
}

char	*check_is_sign(t_node **list, char *line)
{
	char	*buff;

	if (*line == '$')
	{
		if (push_sym_whit_sign(list, line[1]) != ERROR_RETURN)
			return (line + 1);
		if (line[1] == '?')
			return (pushback(list, EXIT_STATUS, "$?"), line + 1);
		else if (*line && line[1] >= '0' && line[1] <= '9')
		{
			buff = malloc(sizeof(char) * 2);
			if (!buff)
				return (NULL);
			buff[0] = line[1];
			buff[1] = 0;
			add(&g_tools.garbage, buff);
			return (pushback(list, SIGN, buff), line + 1);
		}
		else if (*(line + 1))
			return (check_is_wd(list, ++line, SYMBOLS));
		else
			pushback(list, WORD, "$");
	}
	return (line);
}

char	*check_is_quot(t_node **list, char *line, char quot)
{
	char	*buff;
	int		i;

	buff = NULL;
	i = 0;
	if (*line == quot)
	{
		line++;
		if ((ft_strchr(line, quot)))
		{
			while (line[i] != quot)
				i++;
			middle_quets(list, line, quot, i);
			return (ft_strchr(line, quot));
		}
		else
			return (ft_putstr_fd("minishell: unclosed  quotes\n", 2), \
			g_tools.status_sign = 258, NULL);
	}
	return (line);
}

char	*check_is_quot_simple(t_node **list, char *line, char quot)
{
	int		i;

	i = 0;
	if (*line == quot)
	{
		line++;
		if ((ft_strchr(line, quot)))
		{
			while (line[i] != quot)
				i++;
			middle_quets_s(list, line, quot, i);
			return (ft_strchr(line, quot));
		}
		else
			return (ft_putstr_fd("minishell: unclosed  quotes\n", 2), \
			g_tools.status_sign = 258, NULL);
	}
	return (line);
}

int	check_lexer(t_node **list, char *line)
{
	while (*line)
	{
		line = check_is_ws(list, line);
		line = check_is_wd(list, line, " \t\r\n\"'\v\f|<>$");
		line = check_is_pipe(list, line);
		line = check_is_red(list, line);
		line = check_is_sign(list, line);
		line = check_is_quot(list, line, '"');
		if (line == NULL)
			return (ERROR_RETURN);
		line = check_is_quot_simple(list, line, '\'');
		if (line == NULL)
			return (ERROR_RETURN);
		line++;
	}
	return (1);
}
