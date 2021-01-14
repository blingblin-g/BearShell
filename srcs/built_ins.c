#include "mini.h"

int		pwd()
{
	char	buf[2097152];
	char	*working_directory;

	working_directory = getcwd(buf, 2097152);
	write(1, working_directory, ft_strlen(working_directory));
	write(1, "\n", 1);
	get_info()->exit_status = 0;
	return (TRUE);
}

int		cd(char *path)
{
	int		result;

	if (path == 0)
		path = get_env_item("HOME");
	else if (valid_path(path))
	{
		get_info()->exit_status = 1 << 8;
		return(print_error(PATH_ERR, path));
	}
	result = !chdir(path);
	if (!result)
		get_info()->exit_status = 0;
	else
		get_info()->exit_status = 1 << 8;
	return (result);
}

int		echo(char **argv)
{
	int 	is_option;

	is_option = FALSE;
	while (ft_strncmp(argv[1], "-n", 3) == 0)
	{
		is_option = TRUE;
		argv++;
	}
	print_arr(argv + 1);
	if (!is_option)
		write(1, "\n", 1);
	get_info()->exit_status = 0;
	return (TRUE);
}

void	builtin_exit(char *argv)
{
	if (argv == NULL)
		exit(get_info()->exit_status);
	else
		exit((unsigned char)ft_atoi(argv));
}

void free_exit() // memory free 관련 기능 추가하기
{
	exit(0);
}
