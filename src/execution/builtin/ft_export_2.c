/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:07:57 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/30 13:05:38 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_push_to_env(int *status, int *append, char *splited_value, char *cmd)
{
	if (*status == 0 && *append == 0)
		pushback_env(&g_tools.g_env, splited_value, cmd);
	*status = 0;
}

void	ft_err_exp(char *str)
{
	if (str)
		ft_putstr_fd(create_err("minishell: export: `", str, \
					"': not a valid identifier\n"), 2);
}

int	check_cmd_valid(char *cmd)
{
	char	temp;
	char	*sym;
	int		i;

	i = -1;
	sym = "!\"'#$%&()*,-.>?-/\\;<>?@~_";
	if ((cmd[0] >= '0' && cmd[0] <= '9'))
		return (ft_err_exp(cmd), 1);
	while (*cmd)
	{
		temp = *cmd++;
		if (*(cmd + 1) == '+' && *(cmd + 2) == '+')
			return (ft_err_exp(cmd), 1);
		while (*cmd == '=')
		{
			while (sym[++i])
			{
				if (temp == '_')
					return (1);
				if (temp == sym[i])
					return (ft_err_exp(cmd), 1);
			}
			i = -1;
			cmd++;
		}
	}
	return (ERROR_RETURN);
}

void	check_exported_append(char ***splited_value, char ***cmd, int *append)
{
	int		i;
	char	*str;

	i = 0;
	if (strstr(**cmd, "+="))
	{
		while (splited_value[0][0][i])
			i++;
		str = malloc(sizeof(char) * i);
		add(&g_tools.garbage, str);
		i = -1;
		while (splited_value[0][0][++i])
			str[i] = splited_value[0][0][i];
		str[i -1] = 0;
		*splited_value[0] = str;
		**cmd = ft_strjoin(*splited_value[0], "=");
		if (splited_value[0][1])
			**cmd = ft_strjoin(**cmd, splited_value[0][1]);
		*append = 1;
	}
	else
		*append = 0;
}

char	*get_cmd_export(char ***splited_value, char *cmd)
{
	*splited_value = ft_split(cmd, '=');
	if (check_cmd_valid(cmd) != ERROR_RETURN)
		return (NULL);
	if (*splited_value[1] == NULL)
	{
		if (strstr(cmd, "="))
			cmd = ft_strjoin(*splited_value[0], "=  ");
		else
			return (NULL);
	}
	return (cmd);
}
