#include "mini.h"

int		valid_path(char *path)
{
	DIR *directory;

	if ((directory = opendir(path)))
		return (closedir(directory));
	return (TRUE);
}

int		valid_command(char c)
{
	if (ft_strchr("<>|;", c))
	{
		printf("[%p]\n",ft_strchr("<>|;", c));
		return (ERROR);
	}
	return (SUCCESS);
}