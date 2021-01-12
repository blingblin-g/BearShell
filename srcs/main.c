#include <string.h>
#include "mini.h"

int		main()
{
	t_parse	pars;
	char	*command;
	t_pro	*pro_lst;
	t_list	*pipe_lst;

	get_info()->env_list = create_env_list();
	get_info()->process_name = NULL;
	signal(SIGINT, interrupt_handler);
	signal(SIGQUIT, interrupt_handler);
	while (MINISHELL)
	{
		set_process_name(NAME);
		print_prompt();
		if (check_eof(get_next_line(0, &command), &command) == ERROR)
			continue;
		init_pars(&pars);
		if (is_valid_line(&command) == ERROR)
			continue;
		if (main_parse(command, &pars) == ERROR)
		{
			free_parse(&pars, command);
			print_error(PARSING_ERR, NULL);
			continue;
		}
		pro_lst = pars.pro_lst;
		get_info()->std[0] = dup(0);
		get_info()->std[1] = dup(1);
		while (pro_lst)
		{
			pipe_lst = pro_lst->pipe_lst;
			if (piping(&pars, pipe_lst) == ERROR)
				break ;
			pro_lst = pro_lst->next;
		}
		free_parse(&pars, command);
	}
	return (0);
}
