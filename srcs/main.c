/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:33:44 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:33:46 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	piping_iter(t_parse *pars, t_pro *pro_lst)
{
	while (pro_lst)
	{
		if (piping(pars, pro_lst->pipe_lst) == ERROR)
			break ;
		pro_lst = pro_lst->next;
	}
}

int		minishell_iter(t_parse *pars)
{
	char	*command;
	t_pro	*pro_lst;

	command = NULL;
	set_process_name(NAME);
	print_prompt();
	if (check_eof(get_next_line(0, &command), &command) == ERROR)
		return (ERROR);
	init_pars(pars);
	if (is_valid_line(&command) == ERROR)
		return (ERROR);
	if (main_parse(command, pars) == ERROR)
	{
		free_parse(pars, command);
		print_error(PARSING_ERR, NULL);
		return (ERROR);
	}
	pro_lst = pars->pro_lst;
	get_info()->std[0] = dup(0);
	get_info()->std[1] = dup(1);
	piping_iter(pars, pro_lst);
	free_parse(pars, command);
	return (SUCCESS);
}

int		main(int argc, char *argv[], char **environ)
{
	t_parse	pars;

	(void)argc;
	(void)argv;
	get_info()->env_list = create_env_list(environ);
	get_info()->process_name = NULL;
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
	while (MINISHELL)
	{
		if (minishell_iter(&pars) == ERROR)
			continue;
	}
	return (get_info()->exit_status);
}
