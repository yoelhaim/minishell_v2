/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:26:39 by akadi             #+#    #+#             */
/*   Updated: 2022/08/19 20:20:25 by yoelhaim         ###   ########.fr       */
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

void ft_cd(char **cmd)
{
	if(*cmd && !*(cmd +1 ))
	{
		if (chdir(getenv("HOME")) == -1)
			check_folder(getenv("HOME"));
		
	}
	else 
	{
		if (chdir(*(cmd +1)) == -1)
			check_folder(*(cmd +1));
	}
	
}

void ft_pwd(char *next_arg)
{
	char path[1024];
	
	if(next_arg)
		printf("pwd: too many arguments\n");
	else
		printf("%s\n", getcwd(path, 1024));
}

void check_doolar_sign(char *str)
{
	int i =0;
	
	while(*str != '$' && *str)
	   printf("%c", *str++);
	while(str[i])
	{
		if(str[i] == '$')
			i++;
		if(str[i] >= '0' && str[i] <= '9' && str[i -1] == '$')
		{
			i++;
		}
			
		if(str[i] >= 'a' && str[i] <= 'z' && str[i -1] == '$')
		{
			
			while(str[i] != '$' && str[i])
				printf("%c", str[i++]);
				
		}
		printf("%c", str[i]);
		i++;
	}
	   
	
	printf("\n");
}


int ft_echo(char **cmd)
{


	if(cmd[1] == NULL && ft_strcmp(*cmd,"$"))
		return(	printf("\n"), ERROR_RETURN);
	cmd++;
	while(*cmd)
	{

		check_doolar_sign(*cmd);
		// i = check_doolar_sign(*cmd);
		// check_in_env(*cmd + i);
		
		cmd++;
			
	}
	
	return (1);
}