#include "mini.h"

// int		print_error(int type, char *path)
// {
// 	if (type == FORK_ERR)
// 	{
// 		print_err("failed to fork!\n", 2);
// 	}
// 	else if (type == PATH_ERR)
// 	{
// 		print_err("คʕ • ₒ•ʔค ❤❤❤ cd: ", 2);
// 		print_err(path, 2);
// 		print_err(": No such file or directory\n", 2);
// 	}
// 	else if (type == PARSING_ERR)
// 	{
// 		print_err("คʕ;•̀ ᴥ•́ʔค ❤❤❤ syntax error!\n", 2);
// 	}
// 	else if (type == COMMAND_ERR)
// 	{
// 		print_err("คʕ •̀ o•́ʔค ❤❤❤ command not found\n", 2);
// 	}
// 	return (ERROR);
// }

// int		valid_command(char c)
// {
// 	if (ft_strchr("<>|;", c))
// 	{
// 		printf("[%p]\n",ft_strchr("<>|;", c));
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }