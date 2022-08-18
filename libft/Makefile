# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoelhaim <yoelhaim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 11:18:45 by yoelhaim          #+#    #+#              #
#    Updated: 2021/11/20 13:52:26 by yoelhaim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
INC = libft.h
CRT := ar -crs
REMOVE := rm -rf

SRCS = ft_atoi.c \
	  ft_bzero.c \
	  ft_isalnum.c \
	  ft_isalpha.c \
	  ft_isascii.c \
	  ft_isdigit.c \
	  ft_isprint.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memcpy.c \
	  ft_memset.c \
	  ft_strlcat.c \
	  ft_strchr.c \
	  ft_strlcpy.c \
	  ft_strlen.c \
	  ft_strrchr.c \
	  ft_strnstr.c \
	  ft_strncmp.c \
	  ft_strdup.c \
	  ft_calloc.c \
	  ft_memmove.c \
	  ft_toupper.c\
	  ft_tolower.c\
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putnbr_fd.c \
	  ft_substr.c \
	  ft_strmapi.c \
	  ft_putendl_fd.c \
	  ft_strjoin.c \
	  ft_itoa.c \
	  ft_striteri.c \
	  ft_split.c \
	  ft_strtrim.c \


SRCSBONUS = ${SRCS} \
	  ft_lstnew.c \
	  ft_lstadd_front.c \
	  ft_lstadd_back.c \
	  ft_lstdelone.c \
	  ft_lstsize.c \
	  ft_lstlast.c \
	  ft_lstclear.c \
	  ft_lstiter.c \

OBJS := $(SRCS:.c=.o)

OBJSB := $(SRCSBONUS:.c=.o)

all: $(NAME)

bonus: $(OBJSB)
	$(CRT) $(NAME) $^


$(NAME): $(OBJS) $(INC)
	$(CRT) $@ $^
%.o: %.c
	cc $(FLAGS) -c $< -o $@


clean:
	$(REMOVE) $(OBJS) $(OBJSB)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all
