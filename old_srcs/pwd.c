#include "mini.h"

// char *getcwd(char *buf, size_t size)

int		pwd()
{
	char	buf[2097152];

	return (getcwd(buf, 2097152));
}