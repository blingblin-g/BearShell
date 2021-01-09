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