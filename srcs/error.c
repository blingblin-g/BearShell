#include "mini.h"

int		print_error(int type, char *path)
{
	if (type == FORK_ERR)
	{
		ft_putstr_fd("failed to fork!\n", 2);
	}
	else if (type == PATH_ERR)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (ERROR);
}