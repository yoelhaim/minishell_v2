/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:33 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/18 23:49:37 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_globals	g_tools = {0};

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
		{
			free(line);
			continue ;
		}
		if (check_lexer(&data, line) == ERROR_RETURN)
		{
			clear_list(&data);
			continue ;
		}
		if (syntax_error(data) == ERROR_RETURN)
			clear_list(&data);
		cmd = parse(data);
		exec_cmd(cmd);
		clear_list(&data);
	}
}

int	main(int ac, char **av, char **envr)
{
	t_cmd	*cmd;
	t_node	*data;

	(void)av;
	if (ac != 1)
		return (printf("ERROR"), 0);
	create_env(envr);
	// printf(" is upp %s\n", setUpper("sggdgHHH"));
	setup_shell (&data, &cmd);
	free_all (g_tools.garbage);
	rl_clear_history();
	return (0);
}
