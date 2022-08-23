/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:54:42 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/23 12:40:34 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_is_wd(t_node **list, char *line, char *sc)
{
	char	*buff;
	int		i;

	i = 0;
	while (!ft_strchr(sc, line[i]))
		i++;
	buff = malloc(sizeof(char) * i + 1);
	add(&g_tools.garbage, buff);
	i = 0;
	while (*line && !ft_strchr(sc, *line))
	{
		buff[i] = *line;
		line++;
		i++;
	}
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
	char	*symbols;
	char	*buff;

	symbols = " \t\n!\"%'()*+,-./:;<=>?@[\\]^`|~$";
	if (*line == '$')
	{
		if (line[1] == '?')
			return (pushback(list, EXIT_STATUS, "$?"), line + 1);
		else if (*line && line[1] >= '0' && line[1] <= '9')
		{
			buff = malloc(sizeof(char) * 2);
			buff[0] = line[1];
			buff[1] = 0;
			add(&g_tools.garbage, buff);
			return (pushback(list, SIGN, buff), line + 1);
		}
		else if (*(line + 1))
			return (check_is_wd(list, ++line, symbols));
		else
			pushback(list, WORD, "$");
	}
	return (line);
}

static char	*check_is_quot(t_node **list, char *line, char quot)
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
			return (printf("minishell: unclosed  quotes\n"), NULL);
	}
	return (line);
}

static char	*check_is_quot_simple(t_node **list, char *line, char quot)
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
			middle_quets(list, line, quot, i);
			return (ft_strchr(line, quot));
		}
		else
			return (printf("minishell: unclosed  quotes\n"), NULL);
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
