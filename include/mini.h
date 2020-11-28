/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:30:37 by sooyoon           #+#    #+#             */
/*   Updated: 2020/11/16 23:11:51 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

/*
* boolean
*/

# define FALSE 0
# define TRUE 1

/*
* need to add error
*/

# define ERROR 0
# define NOT_FOUND -1
# define SUCCESS 1

# define PIPE 1
# define INPUT 2
# define OUTPUT 3
# define APPEND 4
# define SEMI 5
# define END 6

typedef struct	s_info
{
	t_list		*env_list;
}				t_info;

/*
* cmd_lst : command list
* pro_lst : process list
*/

// typedef struct	s_pro_lst
// {
// 	int			type;
// 	t_list		*next;
// 	t_list		*cmd_lst;
// }				t_pro_lst;

typedef struct		s_pro
{
	int				type;
	char			*raw;
	t_list			*cmd_lst;
	struct s_pro	*next;
}					t_pro;


typedef struct	s_parse
{
	int			is_space;
	int			single_q;
	int			double_q;
	int			start;
	char		*line;
	// t_list		*cmd_lst;
	t_pro		*pro_lst;
}				t_parse;

int		get_next_line(int fd, char **line);
char	*get_env_item(char *key);
int		echo(char **argv);
t_list	*create_env_list();
t_info	*get_info();
void	export(char *argv);
void	print_str(void *str);
int		find_chr(char *str, char ch);
void	env();
void	unset(char *argv);
int		is_single_quote_zone(t_parse *pars, int *i, char **content);
int		main_parse(char *line);
t_pro	*new_prolst(char *raw, int type);
t_pro	*last_prolst(t_pro *lst);
void	add_back_prolst(t_pro **lst, t_pro *new);
void	print_prolst(t_pro *lst);

#endif