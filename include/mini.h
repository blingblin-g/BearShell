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

typedef struct	s_info
{
	t_list		*env_list;
}				t_info;

int		get_next_line(int fd, char **line);
char	*get_env_item(char *key);
int		echo(char **argv);
t_list	*create_env_list();
t_info	*get_info();
void	export(char *argv);
void	print_str(void *str);
void	env();

#endif