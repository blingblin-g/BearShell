#include "mini.h"

int		print_error(int type, char *path)
{
	if (type == FORK_ERR)
	{
		ft_putstr_fd("failed to fork!\n", 2);
	}
	else if (type == PATH_ERR)
	{
		ft_putstr_fd("คʕ • ₒ•ʔค ❤❤❤ cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (type == PARSING_ERR)
	{
		ft_putendl_fd("คʕ;•̀ ᴥ•́ʔค ❤❤❤ syntax error!", 2);
	}
	else if (type == COMMAND_ERR)
	{
		ft_putendl_fd("คʕ •̀ o•́ʔค ❤❤❤ command not found", 2);
	}
	return (ERROR);
}

int		valid_command(char c)
{
	if (ft_strchr("<>|;", c))
		return (ERROR);
	return (SUCCESS);
}