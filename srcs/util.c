#include "mini.h"

void	print_str(void *str)
{
	ft_putendl_fd((char *)str, 0);
}

t_info *get_info()
{
	static t_info info;
	return &info;
}