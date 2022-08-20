NAME = minishell

INC = minishell.h  \
	libft/libft.h

READLINE = $(shell brew --prefix readline)

INCLUDE_READLINE = $(addprefix $(READLINE),/include)

LIB_READLINE = $(addprefix $(READLINE),/lib)
FILES_SRC = src
FILES_EXEC = src/execution
FILES_UT = $(FILES_SRC)/utils_function
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a 



CC = cc -Wall -Wextra -Werror

SRC = $(FILES_SRC)/main.c \
	$(FILES_SRC)/read_line.c \
	$(FILES_SRC)/lixer.c \
	$(FILES_SRC)/expander.c \
	$(FILES_EXEC)/exec.c \
	$(FILES_EXEC)/ft_builtin.c \
	$(FILES_EXEC)/ft_builtin2.c \
	$(FILES_EXEC)/utils_exec.c \
	$(FILES_EXEC)/redirect_file.c \
	$(FILES_SRC)/forfree.c \
	$(FILES_SRC)/parse.c \
	$(FILES_SRC)/list_red.c \
	$(FILES_SRC)/list_cmd.c \
	$(FILES_SRC)/list_utils.c \
	$(FILES_SRC)/error_syntax.c \
	$(FILES_UT)/utils.c \
	$(FILES_UT)/list_env.c \
	$(FILES_UT)/create_env.c \



OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) -I $(INCLUDE_READLINE) -c $< -o $@ -g

all : $(NAME)

$(NAME) : $(INC)  $(OBJ) $(LIBFT_LIB)
	$(CC)  -I $(INCLUDE_READLINE) -L $(LIB_READLINE) -lreadline $(LIBFT_LIB) $(OBJ) -o $(NAME) -g

$(LIBFT_LIB) :
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) fclean -C $(LIBFT_DIR)
fclean : clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)
re: fclean all