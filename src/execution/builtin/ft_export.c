/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:05:02 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/09/03 22:16:46 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_printf_exported(char **export)
{
	int		i;
	char	**spl;

	i = -1;
	while (export[++i])
	{
		spl = ft_split(export[i], '=');
		if (spl[1] != NULL || ft_strstr(spl[0], "="))
			printf("declare -x %s=\"%s\"\n", spl[0], spl[1]);
		else
			printf("declare -x %s\n", spl[0]);
	}
}

void	printf_export(char **str)
{
	char	**export;
	int		i;
	char	*variable;

	i = 0;
	export = str;
	variable = NULL;
	while (i <= size_of_env() && export[i + 1])
	{
		if (export[i][0] > export[i + 1][0])
		{
			variable = export[i + 1];
			export[i + 1] = export[i];
			export[i] = variable;
			i = 0;
		}
		else
			i++;
	}
	ft_printf_exported(export);
}

void	getexport(void)
{
	t_env	*env;
	int		i;
	char	**str;

	i = 0;
	str = NULL;
	env = g_tools.g_env;
	while (env)
	{
		i++;
		env = env->next;
	}
	str = malloc(sizeof(char *) * i + 1);
	if (!str)
		return ;
	add(&g_tools.garbage, str);
	i = 0;
	env = g_tools.g_env;
	while (env)
	{
		str[i++] = env->value;
		env = env->next;
	}
	str[i] = 0;
	printf_export(str);
}

int	add_new_var(char **cmd, int is_append, char *var, char *val)
{
	while (*cmd)
	{
		if (err_arg(cmd))
			return (ft_putstr_fd(create_err(ERR_F, *cmd, ERR_L), 2) \
					, 404);
		if ((check_is_valid_var(get_var(*cmd), 0) == -1))
			return (ft_putstr_fd(create_err(ERR_F, *cmd, ERR_L), 2), 404);
		if (checkappend(*cmd))
			is_append = 1;
		var = get_var(*cmd);
		if (ft_strchr(*cmd, '='))
			val = ft_strchr(*cmd, '=') + 1;
		if (is_append)
			var = ft_substr(var, 0, ft_strlen(var) - 1);
		if ((check_is_valid_var(get_var(var), 1) == -2))
			return (ft_putstr_fd(create_err(ERR_F, *cmd, ERR_L), 2), \
					ERROR_RETURN);
		if (check_is_in_env(var))
			add_new_var_env(var, val);
		else
			update_var_env(var, val, is_append);
		is_append = 0;
		cmd++;
	}
	return (1);
}

void	ft_export(char **cmd)
{
	int		is_append;
	char	*val;
	char	*var;

	val = NULL;
	var = NULL;
	is_append = 0;
	cmd++;
	if (*cmd != NULL)
		add_new_var(cmd, is_append, var, val);
	else
		getexport();
}
