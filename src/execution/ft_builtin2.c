/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:26:39 by akadi             #+#    #+#             */
/*   Updated: 2022/08/19 17:39:09 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	printafternember(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar_fd(str[i], 1);
	ft_putchar_fd('\n', 1);
}

void	check_in_env(char *str)
{
	t_env	*env;
	int status;

	env = g_tools.g_env;
	status = 0;
	if ((str[0] >= '0' && str[0] <= '9') && str[1] == '\0')
	{
		ft_putendl_fd("", 1);
		return ;
	}
	else if((str[0] >= '0' && str[0] <= '9') && str[1] != '\0')
		printf("%s\n", str + 1);
	 
	while (env)
	{
		if (!ft_strcmp(str, env->variable))
		{
			printf("%s\n", strstr(env->value, "=") + 1);
			break ;
		}
		env = env->next;
	}
	// if (str2)
	// 	printafternember(str2);
}

void check_doolar_sign(char *s)
{
	int i;

	i = -1;

	while(s[++i])
	{
		if(s[i] == '$' && ( s[i + 1] >= '0' && s[i + 1] <= '9'))
			printf("%s\n", s  +1);
		else if(s[i] == '$' && ( s[i + 1] >= 'a' && s[i + 1] <= 'z'))
		  	printf("%s\n", s + 1);
		else if(s[i] == '$' && ( s[i + 1] >= 'A' && s[i + 1] <= 'Z'))
		  	printf("%s\n", s + 1);
		else if(s[i] == '$' && (s[i + 1] == '?' ))
		  	printf("%s\n", s + 1);
		// else
		// 	printf("%c", s[i]);	
	}

	
}


int ft_echo(char **cmd)
{


	if(cmd[1] == NULL && ft_strcmp(*cmd,"$"))
		return(	printf("\n"), ERROR_RETURN);
	
	while(*cmd)
	{

		check_doolar_sign(*cmd);
		// i = check_doolar_sign(*cmd);
		// check_in_env(*cmd + i);
		
		cmd++;
			
	}
	
	return (1);
}