#include "mini.h"

void	print_str(void *str)
{
	ft_putendl_fd((char *)str, 1);
}

void	print_err(void *str)
{
	ft_putstr_fd((char *)str, 2);
}

void	print_arr(char **arr)
{
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (arr + 1 != 0)
			write(1, " ", 1);
		arr++;
	}
}

void	println_arr(char **arr)
{
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (arr + 1 != 0)
			write(1, "\n", 1);
		arr++;
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
		print_err(": No such file or directory\n");
	}
	else if (type == PARSING_ERR)
		print_err("คʕ;•̀ ᴥ•́ʔค ❤❤❤ syntax error!\n");
	else if (type == COMMAND_ERR)
		print_err("คʕ •̀ o•́ʔค ❤❤❤ command not found\n");
	return (ERROR);
}