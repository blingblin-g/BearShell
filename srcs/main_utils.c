#include "mini.h"

void	print_prompt()
{
	char	*prompt;

	prompt = "คʕ • ﻌ•ʔค ❤❤❤ ";
	ft_putstr_fd(prompt, 1);
}

void	interrupt_handler(int sig)
{
	if (get_info()->is_minishell)
		return ;
	if (sig == SIGINT) // Ctrl+C
	{
		if (!ft_strcmp(NAME, get_info()->process_name))
		{
			ft_putendl_fd("\b\b  \b\b", 1);
			print_prompt();
		}
		else if (get_info()->process_index == 1)
			ft_putstr_fd("\n", 2);
	}
	else if (sig == SIGQUIT) // Ctrl+백슬래시
	{
		if (!ft_strcmp(NAME, get_info()->process_name))
			ft_putstr_fd("\b\b  \b\b", 1);
		else if (get_info()->process_index == 1)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}


int		check_eof(int gnl_value, char **command)
{
	if (gnl_value == 0)
	{
		if (!ft_strcmp(*command, ""))
		{
			ft_putstr_fd("exit\n", 1);
			free(*command);
			exit(0);
		}
		else
		{
			write(1, "\n", 1);
		}
	}
	return (SUCCESS);
}