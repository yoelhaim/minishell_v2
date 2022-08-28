/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:53:47 by yoelhaim          #+#    #+#             */
/*   Updated: 2022/08/28 15:53:51 by akadi            ###   ########.fr       */
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
# include <stdbool.h>

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
# define STR_IGN " \t\r\n\"'\v\f|<>$"
# define STR_IGN_DOOLAR " \t\r\n\"'\v\f|<>>"
//exit without new line
# define MOVE_UP_RIGHRT "\033[1A\033[12C"

// error message
# define TOKEN_ERR "minishell: syntax error, \
 near unexpected token `'"
# define NL_ERROR_MESSSAGE "minishell: syntax error \
 near unexpected token `newline' '"
// fin error message

extern t_globals	g_tools;

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
	t_env		*g_env;
	t_node_free	*garbage;
	int			status_sign;
	int			shlvl;
	int			r_in;
	int			w_out;
	int			fdd;
	int			dup_in;
	int			dup_out;
	int			fd[2];
}	t_globals;

typedef struct s_red
{
	int				type;
	char			*filename;
	struct s_red	*next;
}	t_red;

// linked list commonds
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
int		size_of_env(void);

char	*read_line(void);
int		is_ws(char *line);

//node list
t_node	*new_node(int type, char *val);
void	pushback(t_node **lst, int type, char *val);
t_node	*clear_list(t_node **lst);
//redirection list
t_red	*new_node_red(int type, char *val);
void	pushback_red(t_red **lst, int type, char *val);
t_red	*clear_list_red(t_red **lst);
//commond list
void	pushback_cmd(t_cmd **lst, char **arg, t_red *red);
t_cmd	*new_node_cmd(char **arg, t_red *red);
t_cmd	*clear_list_cmd(t_cmd **lst);
int		size_of_cmd(t_cmd **list);
//lixer and tokenzer
int		check_lexer(t_node **list, char *line);
int		syntax_error(t_node *list);
void	intail_env(char **data);
int		ft_strcmp(char *s1, char *s2);
t_cmd	*parse(t_node *list);
char	*check_is_ws(t_node **list, char *line);
char	*check_is_pipe(t_node **list, char *line);
char	*middle_quets(t_node **list, char *line, char quot, int i);
char	*check_is_sign(t_node **list, char *line);
char	*check_is_wd(t_node **list, char *line, char *sc);
char	*check_is_red(t_node **list, char *line);
void	expander(t_node **list);
void	check_expand_status(char **value);
char	*middle_quets_s(t_node **list, char *line, char quot, int i);
//free 
void	add(t_node_free **garbage, void *pointer);
void	free_all(t_node_free *garbage);
// execution
void	exec_cmd(t_cmd *cmd, t_node *list);
char	*get_path(void);
char	**export_env(t_env *env);
char	*setUpper(char *str);
void	ft_builtin(char **cmd);
int		size_word(char **cmd);
int		check_valid_export(char **cmd);
int		ft_echo(char **cmd);
void	ft_cd(char **cmd);
int		check_folder(char *name);
void	ft_pwd(void);
int		check_redirecrt(t_red *red, int *status);
int		check_builtin(char *cmd);
int		print_cmnd(char **cmd);
// next_ exec part 2
// void	check_status_file(int status, int *in, int *out);
int		check_is_one_cmnd(t_cmd *cmd, t_node *list, int *i);
void	child_process(t_cmd *cmd, int *status);
// function export and unset cd
char	*get_cmd_export(char ***splited_value, char *cmd);
void	next_export(char **cmd, char **splited_value \
	, int status, t_env *env);
void	ft_export(char **cmd);
t_env	*ft_unset(char **cmd);
int		check_cmd_valid(char *cmd);
void	check_exported_append(char ***splited_value, char ***cmd, int *append);
void	is_red(t_red *cmd, int *status);
void	ft_cd(char **cmd);
// red 
void	open_redout(char *filename);
void	open_append(char *filename);
int		open_in(char *filename, int *status);
char	*create_err(char *firs_s, char *midl_s, char *last_s);
#endif