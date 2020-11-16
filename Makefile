# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 22:46:22 by sooyoon           #+#    #+#              #
#    Updated: 2020/11/16 23:12:29 by sooyoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	-I ./include -I ./Libft
LIB		=	-L ./Libft -lft
CFLAGS	=	-Wall -Wextra -Werror
LIB_SRC	=	./Libft
SRCS	=	./srcs/get_next_line.c	\
			./srcs/echo.c	\
			./srcs/search_env.c	\
			./srcs/util.c	\
			./srcs/export.c	\
			./srcs/test.c
			# ./srcs/main.c

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