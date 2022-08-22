/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:15:33 by akadi             #+#    #+#             */
/*   Updated: 2022/08/22 22:48:19 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void 	printf_export(char **str)
{
	char **export;
	int		i;
	char	*variable=  NULL ;
	
	i = 0;
	export = str;
	while(i <= size_of_env() && export[i + 1] )
	{
		if(export[i][0]  > export[i + 1][0])
		{
			variable = export[i + 1];
			export[i + 1]= export[i];
			export[i] = variable;
			i = 0;
		}
		else
			i++;
	}
	i =0;
	while(export[i])
	{
		printf("declare -x %s\n", export[i++]);
	}
	
}

void getexport()
{
	t_env *env;
	int i = 0;
	
	char **str;
	env = g_tools.g_env;
	while(env)
	{
		i++;
		// printf("declare -x %s\n", env->value);
		env= env->next;
	}
	str = malloc(sizeof(char *)* i);
	i = 0;
	env = g_tools.g_env;
		while(env)
	{
		str[i] = env->value;
		i++;
		// printf("declare -x %s\n", env->value);
		env= env->next;
	}
	printf_export(str);
}

void	ft_export(char **cmd)
{
	t_env	*env;
	int		status;
	char	**splited_value;

	env = g_tools.g_env;
	status = 0;
	splited_value = NULL;
	if(check_valid_export(cmd) == ERROR_RETURN)
	{
		printf("minishel: export: `=': not a valid identifier\n");
		return ;
	}
	cmd++;
	if(*cmd != NULL)
		next_export(cmd, splited_value, status, env);
	else
		getexport();
		
	
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
			printf("exit \nminishell: exit: %s: numeric argument required\n", cmd[i]);
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
	if (!ft_strcmp(*cmd, "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(*cmd, "cd"))
		ft_cd(cmd);
	if (!ft_strcmp(*cmd, "pwd"))
		ft_pwd(*(cmd + 1));
	if (!ft_strcmp(*cmd, "unset"))
		g_tools.g_env = ft_unset(cmd);

}
