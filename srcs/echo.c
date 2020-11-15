#include "mini.h"

void	print_arr(char **arr) // input after pointer calc
{
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (arr + 1 != 0)
			write(1, " ", 1);
		arr++;
	}
}

	// if (ft_strncmp(argv[0], "echo", 5)
int		echo(char **argv)
{
	if (ft_strncmp(argv[1], "-n", 3))
		print_arr(argv + 1);// no new line && need to handle quote and double quote
	else
	{
		print_arr(argv + 2);
		write(1, "\n", 1);
	}// join all && need a white space between them
	return (0);
}