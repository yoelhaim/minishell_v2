/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:48:33 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/29 19:32:58 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_globals	g_tools = {0};

void test(t_node **data)
{
	t_node *tmp = *data;
	while (tmp)
	{
		printf("---------------\n");
		printf("---value %s\n", tmp->val);
		printf("---type %d\n", tmp->type);
		printf("------------------\n");
		
	tmp = tmp->next;
	}
	
}


void	clear_and_free(t_node **list, t_cmd **cmd, char *line)
{
	(void) cmd;
	clear_list(list);
	free(line);
}

void	ren_shlvl(char **envr)
{
	t_env	*env;
	int		i;
	int		value;
	char	*input;

	i = -1;
	value = 0;
	env = g_tools.g_env;
	while (envr[++i])
	{
		if (ft_strnstr(envr[i], "SHLVL", ft_strlen(envr[i])))
			value = ft_atoi(ft_strnstr(envr[i], "SHLVL", \
			ft_strlen(envr[i] +1)) + 6);
	}
	while (env)
	{
		if (ft_strnstr("SHLVL", env->variable, 6))
		{
			input = ft_strjoin("SHLVL=", ft_itoa(value + 1));
			env->value = input;
			break ;
		}
		env = env->next;
	}
}

void	setup_shell(t_node **data, t_cmd **cmd)
{
	char	*line;
(void ) cmd;
	while (1)
	{
		line = read_line();
		if (!line || !is_ws(line))
			continue ;
		if (check_lexer(data, line) == ERROR_RETURN)
		{
			clear_list(data);
			continue ;
		}
		if (syntax_error(*data) == ERROR_RETURN)
		{
			clear_list(data);
			continue ;
		}
		// test(data);
		expander(data);
		
		*cmd = parse(*data);
		exec_cmd(*cmd, *data);
		clear_and_free(data, cmd, line);
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
	ren_shlvl(envr);
	setup_shell (&data, &cmd);
	free_all (g_tools.garbage);
	rl_clear_history();
	return (0);
}
