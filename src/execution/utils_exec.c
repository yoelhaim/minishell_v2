/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:34:27 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/22 22:09:50 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*set_upper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			printf("%c", str[i]);
		i++;
	}
	return (str);
}

char	**export_env(t_env *env)
{
	t_env	*tmp;
	int		len;
	char	**exported_env;
	int		i;

	i = 0;
	len = 0;
	tmp = env;
	exported_env = NULL;
	while (tmp && ++len)
		tmp = tmp->next;
	exported_env = malloc(sizeof(char *) * len++);
	add(&g_tools.garbage, export_env);
	while (env)
	{
		exported_env[i++] = env->value;
		env = env->next;
	}
	exported_env[i] = NULL;
	return (exported_env);
}

char	*get_path(void)
{
	t_env	*env;

	env = g_tools.g_env;
	while (env)
	{
		if (strstr(env->variable, "PATH"))
			return (strstr(env->value, "=") + 1);
		env = env->next;
	}
	return (NULL);
}

int	size_word(char **cmd)
{
	int	i;

	i = 0;
	if(!*cmd)
		return (ERROR_RETURN);
	while(cmd[i])
		i++;
	return(i);
}

int	check_valid_export(char **cmd)
{
	cmd++; 
	char **str;

	str = cmd;
	while(*str)
	{
		if(!ft_strcmp(*str, "="))
			return(ERROR_RETURN);
		str++;
	}
	str = cmd;
	while(*str)
	{
		if(*str[0] == '=')
			return(ERROR_RETURN);
		str++;
	}
	return(1);
}

int check_cmd_valid(char *cmd)
{
	if(cmd[0] >= '0' && cmd[0] <= '9')
		return (printf("bash: export: `%s': not a valid identifier\n",cmd),1);
	
	return(ERROR_RETURN);
}

void  next_export(char **cmd, char **splited_value,int  status, t_env	*env)
{
	while(*cmd)
	{
	  splited_value = ft_split(*cmd, '=');
	if(check_cmd_valid(*cmd) != ERROR_RETURN)
			return ;
		if(splited_value[1] == NULL)
		{
			if(strstr(*cmd , "="))
				*cmd = ft_strjoin(splited_value[0], "=  ");
			else
				return ;
		}
		
		while (env)
		{	
					
			if(!ft_strcmp(env->variable,splited_value[0]))
			{
				if(strstr(*cmd , "+="))
					{
						*cmd = ft_strjoin(env->value, strstr(env->value, "+=") + 2);
						printf("www %s\n",*cmd) ;
					}
				env->value = *cmd;
				status = 1;
				break;
			}
			else
				status = 0;
			env = env->next;
		}
		if(status == 0)
		{
			if(!strstr(*cmd , "+="))
				pushback_env(&g_tools.g_env, splited_value[0], *cmd);
		}
			
		status = 0;
		cmd++;
	}
	free(splited_value);
}