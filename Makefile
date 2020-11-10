# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 22:46:22 by sooyoon           #+#    #+#              #
#    Updated: 2020/11/10 22:57:22 by sooyoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
INC		=	-I ./include -I ./libft
LIB		=	-L ./libft -lft
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	./srcs/get_next_line.c	\
			./srcs/main.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC) $(LIB)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:		fclean all

rclean:
	re clean