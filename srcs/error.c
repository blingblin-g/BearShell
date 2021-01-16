/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:34:22 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:34:23 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	}
	else if (type == PARSING_ERR)
	{
		print_err("คʕ;•̀ ᴥ•́ʔค ❤❤❤ syntax error!\n");
		get_info()->exit_status = 258 << 8;
	}
	else if (type == COMMAND_ERR)
	{
		print_err("คʕ •̀ o•́ʔค ❤❤❤ command not found\n");
		get_info()->exit_status = 127 << 8;
	}
	return (ERROR);
}
