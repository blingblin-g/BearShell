#include "mini.h"

int		execute_builtin(char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (echo(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (pwd());
	if (!ft_strcmp(argv[0], "export"))
		return (export(argv[1]));
	if (!ft_strcmp(argv[0], "unset"))
		return (unset(argv[1]));
	if (!ft_strcmp(argv[0], "cd"))
		return (cd(argv[1]));
	if (!ft_strcmp(argv[0], "env"))
		return (env());
	if (!ft_strcmp(argv[0], "exit"))
		free_exit(get_info()->exit_status);
	return (NOT_BUILTIN);
}

int		pwd()
{
	char	buf[2097152];
	char	*working_directory;

	working_directory = getcwd(buf, 2097152);
	write(1, working_directory, ft_strlen(working_directory));
	write(1, "\n", 1);
	return (TRUE);
}

int		cd(char *path)
{
	if (path == 0)
		path = get_env_item("HOME");
	else if (valid_path(path))
		return(print_error(PATH_ERR, path));
	return (!chdir(path));
}

int			echo(char **argv)
{
	size_t	size;

	size = len(argv);
	if (size > 2 && !ft_strncmp(argv[1], "-n", 3))
		print_arr(argv + 2);
	else if (size > 1)
	{
		print_arr(argv + 1);
		write(1, "\n", 1);
	}
	else if (size == 1)
		write(1, "\n", 1);
	return (TRUE);
}

void free_exit() // memory free 관련 기능 추가하기
{
	exit(0);
}
