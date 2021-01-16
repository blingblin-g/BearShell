/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:34:34 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:41:01 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	print_prompt(void)
{
	char	*prompt;

	prompt = "คʕ • ﻌ•ʔค ❤❤❤ ";
	ft_putstr_fd(prompt, 1);
}

void	interrupt_handler(int sig)
{
	if (get_info()->is_minishell)
		return ;
	if (sig == SIGINT)
	{
		if (!ft_strcmp(NAME, get_info()->process_name))
		{
			ft_putendl_fd("\b\b  \b\b", 1);
			print_prompt();
		}
		else if (get_info()->process_index == 1)
			ft_putstr_fd("\n", 2);
		get_info()->exit_status = 130 << 8;
	}
	else if (sig == SIGQUIT)
	{
		if (!ft_strcmp(NAME, get_info()->process_name))
			ft_putstr_fd("\b\b  \b\b", 1);
		else if (get_info()->process_index == 1)
			ft_putstr_fd("Quit: 3\n", 2);
		get_info()->exit_status = 131 << 8;
	}
}

int		check_eof(int gnl_value, char **command)
{
	if (gnl_value == 0)
	{
		if (!ft_strcmp(*command, ""))
		{
			ft_putstr_fd("exit\n", 2);
			free(*command);
			exit(get_info()->exit_status);
		}
		else
		{
			write(1, "\n", 1);
		}
	}
	return (SUCCESS);
}
