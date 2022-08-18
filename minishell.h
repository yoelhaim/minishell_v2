/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:53:47 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/18 23:14:47 by yoelhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>

# define WSPACE 1		   // ' '
# define PIPE 2			   // |
# define REDIN 3			   // <
# define REDOUT 4		   // >
# define APPEND 5		   // >>
# define HEREDOC 6		   // <<
# define SIGN 9			   // $
# define EXIT_STATUS 10	   // $?
# define WORD 11			   //
# define ERROR_RETURN 404   // error retuen value
# define SUCCESS_RETURN 200 // success retuen value

// error message
# define TOKEN_ERR "minishell: syntax error, \
 near unexpected token `'"
# define NL_ERROR_MESSSAGE "minishell: syntax error \
 near unexpected token `newline' '"
// # define TOKEN_ERROR_MESSSAGE ""
// # define TOKEN_ERROR_MESSSAGE ""
// # define TOKEN_ERROR_MESSSAGE ""
// # define TOKEN_ERROR_MESSSAGE ""
// fin error message

// colors
# define RED_C "\x1B[31m"
# define GREEN_C "\x1B[32m"
# define YELLOW_C "\x1B[33m"
# define BLUE_C "\x1B[34m"
# define WHITE_C "\x1B[0m"
# define BLACK_C "\x1B[1m"
// end colors
typedef struct s_data
{
	char	**env;
	int		status;
}	t_data;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;

}	t_env;

// Garbage Collector !!!
typedef struct s_node_free
{
	void				*pointer;
	struct s_node_free	*next;
}	t_node_free;

typedef struct s_globals
{
	int			g_dollar_question;
	t_env		*g_env;
	t_node_free	*garbage;
}	t_globals;

extern t_globals	g_tools;
typedef struct s_red
{
	int				type;
	char			*filename;
	struct s_red	*next;
}	t_red;

typedef struct s_node
{
	int				type;
	char			*val;
	struct s_node	*next;
}	t_node;

typedef struct s_cmd
{
	int				r_in;
	int				w_out;
	char			**cmnd;
	struct s_red	*red;
	struct s_cmd	*next;
}	t_cmd;

// env
void	pushback_env(t_env **lst, char *path, char *val);
t_env	*new_node_env(char *path, char *val);
t_env	*clear_list_env(t_env **lst);
void	create_env(char *data[]);

char	*read_line(void);
int		is_ws(char *line);
t_node	*new_node(int type, char *val);
void	pushback(t_node **lst, int type, char *val);
t_node	*clear_list(t_node **lst);

t_red	*new_node_red(int type, char *val);
void	pushback_red(t_red **lst, int type, char *val);
t_red	*clear_list_red(t_red **lst);

void	pushback_cmd(t_cmd **lst, char **arg, t_red *red);
t_cmd	*new_node_cmd(char **arg, t_red *red);
t_cmd	*clear_list_cmd(t_cmd **lst);

int		check_lexer(t_node **list, char *line);
int		syntax_error(t_node *list);
void	intail_env(char **data);
int		ft_strcmp(char *s1, char *s2);
t_cmd	*parse(t_node *list);
char	*check_is_ws(t_node **list, char *line);
char	*check_is_pipe(t_node **list, char *line);

void	add(t_node_free **garbage, void *pointer);
void	free_all(t_node_free *garbage);

// execution
void	exec_cmd(t_cmd *cmd);
char	*get_path(void);
char	**export_env(t_env *env);
#endif