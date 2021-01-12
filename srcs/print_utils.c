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

void	print_lst(t_list *lst)
{
	ft_lstiter(lst, print_str);
}
