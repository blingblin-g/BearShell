#include "mini.h"

void env()
{
	ft_lstiter(get_info()->env_list, print_str);
}