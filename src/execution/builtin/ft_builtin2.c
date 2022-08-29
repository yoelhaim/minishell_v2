/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:26:39 by akadi             #+#    #+#             */
/*   Updated: 2022/08/29 12:16:11 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <limits.h>


char *ft_getcwd(void)
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	return (ft_strdup(path)); // TODO : free this allocation !
}

void	ft_pwd(void)
{

	printf("%s\n", ft_getcwd());
}

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

void	check_newline(char **str, int status)
{
	char	*s;

	s = NULL;
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
	check_next_nl(str, &status, s);
	if (*str)
	{
		if (status == 1)
			str++;
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
	int	status;

	status = 0;
	if (cmd[1] == NULL && ft_strcmp(*cmd, "$"))
		return (printf("\n"), ERROR_RETURN);
	cmd++;
	check_newline(cmd, status);
	return (1);
}
