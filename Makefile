# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 22:46:22 by sooyoon           #+#    #+#              #
#    Updated: 2021/01/17 13:38:18 by sooyoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	-I ./include -I ./libft
LIB		=	-L ./libft -lft
CFLAGS	=	-Wall -Wextra -Werror
LIB_SRC	=	./libft
SRCS	=	./srcs/get_next_line.c		\
			./srcs/print_utils.c		\
			./srcs/built_ins.c			\
			./srcs/is_valid.c			\
			./srcs/utils.c				\
			./srcs/env.c				\
			./srcs/exports.c			\
			./srcs/search_env.c			\
			./srcs/parsing_utils.c		\
			./srcs/parsing_utils2.c		\
			./srcs/parsing_utils3.c		\
			./srcs/prolst_utils.c		\
			./srcs/set_items.c			\
			./srcs/get_cmd.c			\
			./srcs/exec_utils.c			\
			./srcs/lst_utils.c			\
			./srcs/free.c				\
			./srcs/fd.c					\
			./srcs/pipe.c				\
			./srcs/redirect.c			\
			./srcs/redir_utils.c		\
			./srcs/parsing.c			\
			./srcs/parse_pipe.c			\
			./srcs/quotes_zone.c		\
			./srcs/quotes_zone_util.c 	\
			./srcs/process_quotes.c		\
			./srcs/execute.c			\
			./srcs/error.c				\
			./srcs/main_utils.c			\
			./srcs/main.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC)

$(NAME):	$(OBJS)
	@$(MAKE) all -C $(LIB_SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC) $(LIB)

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(LIB_SRC)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIB_SRC)

re:		fclean all

rclean:
	re clean
