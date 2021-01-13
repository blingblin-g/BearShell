#include "mini.h"

int		print_error(int type, char *path)
{
	if (type == FORK_ERR)
		print_err("failed to fork!\n");
	else if (type == PATH_ERR)
	{
		print_err("คʕ • ₒ•ʔค ❤❤❤ cd: ");
		print_err(path);
		print_err(": No such file or directory\n");
	}
	else if (type == PARSING_ERR)
	{
		print_err("คʕ;•̀ ᴥ•́ʔค ❤❤❤ syntax error!\n");
		get_info()->exit_status = 258;
	}
	else if (type == COMMAND_ERR)
	{
		print_err("คʕ •̀ o•́ʔค ❤❤❤ command not found\n");
		get_info()->exit_status = 127;
	}
	return (ERROR);
}