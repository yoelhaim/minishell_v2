/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:54:42 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/20 19:38:43 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_is_red(t_node **list, char *line)
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
char	*check_is_sign(t_node **list, char *line)
{
	char	*symbols;
	char	*buff;
	// int i = -1;

	symbols = " \t\n!\"$%'()*+,-./:;<=>?@[\\]^`|~";
	if (*line == '$')
	{
		if (line[1] == '?')
			return (pushback(list, EXIT_STATUS, "$?"), line + 1);
		else if (*line && line[1] >= '0' && line[1] <= '9')
		{
			buff = malloc(sizeof(char) * 2);
			buff[0] = line[1];
			buff[1] = 0;
			return (pushback(list, SIGN, buff), line + 1);
		}
		
		else if (*line)
		{
			// int i = -1;
			// while (symbols[++i])
			// {
			// 	int j= -1;
			// 	while(line[++j])
			// 	{
			// 		//printf("dollar %c\n", line[j]);
			// 	if (line[j] == symbols[i])
			// 		{
			// 			//printf ("ishere line => %s\n",line);
			// 			return (line );
			// 		}
			// 	}
			// }
			
			return(check_is_wd(list, ++line, symbols));
		}
		else
			pushback(list, WORD, "$");
	}
	return (line);
}
 char	*check_is_wd(t_node **list, char *line, char *sc)
{
	char	*buff;
	int		i;
	// int		j;

	i = 0;
	while (!ft_strchr(sc, line[i]) && *line )
		i++;
	buff = malloc(sizeof(char) * i + 1);
	i = 0;
	while (line[i] && !ft_strchr(sc, line[i]))
	{
		buff[i] = line[i];
		i++;
	}
	if (i != 0)
	{
		buff[i] = 0;
		// printf("|%s|  \n", buff );
		if (ft_strlen(sc) == 12 || ft_strlen(sc) == 1)
			return (pushback(list, WORD, buff),&line[i - 1]);
		else
			return (pushback(list, SIGN, buff),&line[i +]);
	
	}
	return (line);
}



static char	*check_is_quot(t_node **list, char *line, char quot)
{
	char	*buff;
	int		i;

	i = 0;
	if (*line == quot)
	{
		line++;
		if ((ft_strchr(line, quot)))
		{
			while (line[i] != quot && line[i])
				i++;
			if (i == 0 && *(line + 1) == '\0')
			{
				pushback(list, WSPACE, " ");
				return (" ");
			}
			buff = malloc(sizeof(char) * (i + 1));
			add(&g_tools.garbage, buff);
			if (!buff)
				return (NULL);
			i = 0;
			
			while (line[i] && line[i] != quot)
			{
				if(line[i] == 32)
					line[i] = '\t';
				buff[i] = line[i];
				i++;
			}
			buff[i] = 0;
			while (*buff != 0)
			{
				buff = check_is_wd(list, buff, "$");
				buff = check_is_sign(list, buff);
				buff++;
			}
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
		line = check_is_sign(list, line);
		line = check_is_wd(list, line, " \t\r\n\"'\v\f|<>$");
		line = check_is_pipe(list, line);
		line = check_is_red(list, line);
		
		line = check_is_quot(list, line, '"');
		if (line == NULL)
			return (ERROR_RETURN);
		line = check_is_quot(list, line, '\'');
		if (line == NULL)
			return (ERROR_RETURN);
		line++;
	}
	return (1);
}
