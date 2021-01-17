/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:34:22 by chlim             #+#    #+#             */
/*   Updated: 2021/01/17 23:12:36 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	parsing_error()
{
	if (errno != 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		get_info()->exit_status = 1 << 8;
	}
	else
	{
		print_err("คʕ;•̀ ᴥ•́ʔค ❤❤❤ syntax error!\n");
		get_info()->exit_status = 258 << 8;
	}
}

void	command_error()
{
	if (errno != 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		get_info()->exit_status = 1 << 8;
	}
	else
	{
		print_err("คʕ •̀ o•́ʔค ❤❤❤ command not found\n");
		get_info()->exit_status = 127 << 8;
	}
}

int		print_error(int type, char *path)
{
	if (type == FORK_ERR)
		print_err("failed to fork!\n");
	else if (type == PATH_ERR)
	{
		print_err("คʕ • ₒ•ʔค ❤❤❤ cd: ");
		print_err(path);
		print_err(": ");
		print_err(strerror(errno));
		print_err("\n");
		free(path);
	}
	else if (type == PARSING_ERR)
		parsing_error();
	else if (type == COMMAND_ERR)
		command_error();
	return (ERROR);
}
