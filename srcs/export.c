#include "mini.h"

static void	print_str(void *str)
{
	printf("%s\n", (char *)str);
}

void export(char *key, char *value)
{
	key = 0;
	value = 0;
	ft_lstiter(get_info()->env_list, print_str);
}