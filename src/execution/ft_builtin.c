/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:33 by akadi             #+#    #+#             */
/*   Updated: 2022/08/19 13:32:29 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(char **cmd)
{
	(void)cmd;
	t_env	*env;
	int		status;
	char	**splited_value;
	
	env = g_tools.g_env;
	status = 0;
	if(check_valid_export(cmd) == ERROR_RETURN)
	{
		printf("minishel: export: `=': not a valid identifier\n");
		return ;
	}
	splited_value = ft_split(cmd[1], '=');
	// printf("sppppl    %s\n", splited_value);
	if(splited_value[0] == NULL)
		return ;
	while(env)
	{
		if(!ft_strcmp(env->variable,splited_value[0]))
		{
			env->value = cmd[1];
			status = 1;
			return ;
		}
			
		env = env->next;
	}
	if(status == 0)
		pushback_env(&g_tools.g_env, splited_value[0], cmd[1]);
	
}

t_env	*ft_unset(char **cmd)
{
	t_env	*list;
	t_env	*tmp;
	t_env	*prev;
	int i;
	
	i = 0;
	list = g_tools.g_env;
	tmp = g_tools.g_env;
	prev = g_tools.g_env;
	tmp =  tmp->next;
	if (!ft_strcmp(prev->variable, cmd[1]))
		{
			list = list->next;
			return (list);
		}
	cmd++;
	while (*(cmd))
	{
		tmp = list->next;
		prev = list;
		while( tmp)
		{
			if(!ft_strcmp(tmp->variable, *cmd))
		{
			prev->next = tmp->next;
			break;
		}
		tmp =  tmp->next;
		prev =  prev->next;
		}
		cmd++;
	}
	return (list);
}
void	ft_env(char **cmd)
{
	t_env *env;

	env = g_tools.g_env;
	if(*(cmd+ 1))
	{
		printf("env: %s: No such file or directory\n",*(cmd+ 1) );
		return ;
	}
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
}
void	ft_exit(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "0") || ft_atoi(cmd[i]) > 0 \
		|| ft_atoi(cmd[i]) < 0)
		{	
			printf("exit\n");
			exit (EXIT_FAILURE);
		}
		if (ft_atoi(cmd[i]) == 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	printf("exit\n");
	exit(EXIT_FAILURE);
}

void	ft_builtin(char **cmd)
{
	if (!ft_strcmp(*cmd, "exit"))
		ft_exit (cmd);
	if (!ft_strcmp(*cmd, "env"))
		ft_env(cmd);
	if (!ft_strcmp(*cmd, "export"))
		ft_export(cmd);
	if (!ft_strcmp(*cmd, "unset"))
		g_tools.g_env = ft_unset(cmd);
}
