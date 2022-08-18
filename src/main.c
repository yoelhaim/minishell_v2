/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:33 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/18 20:21:13 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_globals g_tools = {0};

int main(int ac, char **av, char **envr)
{
	t_cmd *cmd;
	char *line;
	t_node *data;
	(void)av;
	(void)envr;
	if (ac != 1)
		return (printf("ERROR"), 0);
	create_env(envr);
	while (1)
	{
		line = read_line();
		if (!line || !is_ws(line))
		{
			free(line);
			continue;
		}
		if (check_lexer(&data, line) == ERROR_RETURN)
		{
			clear_list(&data);
			continue;
		}
		if (syntax_error(data) == ERROR_RETURN)
			clear_list(&data);
		cmd = parse(data);
		exec_cmd(cmd);
		clear_list(&data);
	}
	free_all(g_tools.garbage);
	rl_clear_history();
	return (0);
}
