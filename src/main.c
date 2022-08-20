/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:33 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/20 18:44:55 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_globals	g_tools = {0};

void	clear_and_free(t_node **list, t_cmd **cmd, char *line)
{
	clear_list(list);
	clear_list_cmd(cmd);
	free(line);
}

void test(t_node **list)
{
	t_node *cmd;
	cmd = *list;
	while (cmd)
	{
		printf("value %s type => %d\n", cmd->val, cmd->type);
		cmd = cmd->next;
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
			clear_list(&data);
		expander(&data);
		test(&data);
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
	if (ac != 1)
		return (printf("ERROR"), 0);
	create_env(envr);
	g_tools.status_sign = 0;
	setup_shell (&data, &cmd);
	free_all (g_tools.garbage);
	rl_clear_history();
	return (0);
}
