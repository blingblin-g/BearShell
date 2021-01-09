#include "mini.h"

void	error(int type)
{
	if (type == FORK_ERROR)
	{
		ft_putstr_fd("fork fail\n", 2);
	}
}