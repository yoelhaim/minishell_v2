/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:26:39 by akadi             #+#    #+#             */
/*   Updated: 2022/09/08 12:03:57 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	check_next_nl(char **str, int *status, char *s)
{
	int		i;

	i = 0;
	if (!*str)
		return ;
	if (*str[0] == '-')
	{
		s = *str;
		while (s[++i])
		{
			if (s[i] == 'n' && s[i])
				*status = 1;
			else
			{
				*status = 0;
				break ;
			}
		}
		if (*status == 0)
		{
			printf("%s ", *str);
			*status = 1;
		}
		str++;
	}
}

int	check_first_cmd(char *str, int status)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[++i])
		{
			if (str[i] != 'n')
			{
				status = 1;
				break ;
			}
		}
		if (status == 0)
			return (1);
	}
	return (0);
}

int	search_n(char *s)
{
	int	i;

	i = -1;
	if (ft_strlen(&(s[++i])) == 0)
		return (1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (0);
	}
	return (1);
}

void	check_newline(char **str, int status, int j)
{
	*str = ft_strtrim(*str, " ");
	if (ft_strstr(*str, "-n") && search_n(*str))
	{
		str++;
		while (*str)
		{
			if (!check_first_cmd(*str, status))
				break ;
			str++;
		}
		while (*str)
		{
			printf("%s",*str);
			if (*++str)
				printf(" ");
		}
	}
	else
	{
		while (str[j])
			ft_putstr_fd(ft_strjoin(str[j++], " "), 1);
		printf("\n");
	}
}

int	ft_echo(char **cmd)
{
	int		status;
	int		j;

	j = 0;
	status = 0;
	if (cmd[1] == NULL && ft_strcmp(*cmd, "$"))
		return (printf("\n"), ERROR_RETURN);
	cmd++;
	check_newline(cmd, status, j);
	g_tools.status_sign = 0;
	return (1);
}
