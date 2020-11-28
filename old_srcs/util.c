#include "mini.h"

void	print_str(void *str)
{
	ft_putendl_fd((char *)str, 0);
}

int		find_chr(char *str, char ch)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (-1);
}

t_info *get_info()
{
	static t_info info;
	return &info;
}