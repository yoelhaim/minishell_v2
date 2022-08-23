/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:26:39 by akadi             #+#    #+#             */
/*   Updated: 2022/08/23 10:28:32 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_pwd(char *next_arg)
{
	char	path[1024];

	if (next_arg)
		printf("pwd: too many arguments\n");
	else
		printf("%s\n", getcwd(path, 1024));
}

void	check_next_nl(char **str, int status, char *s)
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
				status = 1;
			else
			{
				status = 0;
				break ;
			}
		}
		if (status == 0)
			printf("%s ", *str);
		str++;
	}
}

int	check_first_cmd(char **str, int status)
{
	int	i;

	i = 0;
	if (str[0][0] == '-' && str[0][1] == 'n')
	{
		while (str[0][++i])
		{
			if (str[0][i] != 'n')
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

void	check_newline(char **str)
{
	char	*s;
	int		status;

	s = NULL;
	status = 0;
	if (check_first_cmd(str, status))
		str++;
	else
	{
		if (*str)
			while (*str)
				printf("%s ", *str++);
		printf ("\n");
		return ;
	}
	check_next_nl(str, status = 0, s);
	if (*str)
	{
		while (*str)
		{
			printf("%s", *str++);
			if (*str)
				printf(" ");
		}
	}
}

int	ft_echo(char **cmd)
{
	if (cmd[1] == NULL && ft_strcmp(*cmd, "$"))
		return (printf("\n"), ERROR_RETURN);
	cmd++;
	check_newline(cmd);
	return (1);
}
