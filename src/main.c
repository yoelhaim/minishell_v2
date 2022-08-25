/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:33 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/25 15:04:09 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_globals	g_tools = {0};

void	clear_and_free(t_node **list, t_cmd **cmd, char *line)
{
	(void) line;
	(void) cmd;
	clear_list(list);
}
void	ren_shlvl(char **envr)
{
	t_env	*env;
	int		i;
	int		value;
	
	i = -1;
	value = 0;
	env = g_tools.g_env;
	while (envr[++i])
	{
		if (ft_strnstr(envr[i], "SHLVL", ft_strlen(envr[i])))
			value = ft_atoi(ft_strnstr(envr[i], "SHLVL", ft_strlen(envr[i]))+ 6);
	}
	while (env)
	{
		if (ft_strnstr(env->variable, "SHLVL", ft_strlen(env->variable)))
		{
			 env->value = ft_strjoin("SHLVL=",  ft_itoa(value + 1));
			 break ;
		}
		env = env->next;
	}
}

void	setup_shell(t_node **datas, t_cmd **cmds)
{
	char	*line;
	t_cmd	*cmd;
	t_node	*data;

	cmd = *cmds;
	data = *datas;
	while (1)
	{
		line = read_line();
		if (!line || !is_ws(line))
			continue ;
		if (check_lexer(&data, line) == ERROR_RETURN)
		{
			clear_list(&data);
			continue ;
		}
		if (syntax_error(data) == ERROR_RETURN)
		{
			clear_list(&data);
			continue ;
		}
		expander(&data);
		cmd = parse(data);
		exec_cmd(cmd);
		clear_and_free(&data, &cmd, line);
	}
}

int	main(int ac, char **av, char **envr)
{
	t_cmd	*cmd;
	t_node	*data;

	(void)av;
	(void)envr;
	if (ac != 1)
		return (printf("ERROR"), 0);
	create_env(envr);
	ren_shlvl(envr);
	setup_shell (&data, &cmd);
	free_all (g_tools.garbage);
	rl_clear_history();
	return (0);
}
