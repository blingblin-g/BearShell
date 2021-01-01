#include "mini.h"

int		valid_path(char *path)
{
	DIR *directory;

	if ((directory = opendir(path)))
		return (closedir(directory));
	return TRUE;
}

int		cd(char *argv)
{
	char *path;

	path = NULL;
	if (argv == 0)
		path = get_env_item("HOME");
	if (valid_path(path))
		return(0);
	return chdir(path);
}

int			echo(char **argv)
{
	if (!ft_strncmp(argv[1], "-n", 3))
		print_arr(argv + 2);
	else
	{
		print_arr(argv + 1);
		write(1, "\n", 1);
	}
	return (TRUE);
}

void free_exit() // memory free 관련 기능 추가하기
{
	exit(0);
}

int		pwd()
{
	char	buf[2097152];
	char	*working_directory;

	working_directory = getcwd(buf, 2097152);
	write(1, working_directory, ft_strlen(working_directory));
	return (TRUE);
}
