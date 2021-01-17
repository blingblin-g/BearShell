/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:31:41 by chlim             #+#    #+#             */
/*   Updated: 2021/01/17 00:17:55 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		pwd(void)
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
		return (print_error(PATH_ERR, path));
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
	int		is_option;

	is_option = FALSE;
	if (argv[1] == NULL)
	{
		write(1, "\n", 1);
		return (TRUE);
	}
	while (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
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

int		builtin_exit(char **argv)
{
	size_t	size;

	size = len(argv);
	if (size == 1)
		exit(get_info()->exit_status);
	else if (size == 2)
		exit((unsigned char)ft_atoi(argv[1]));
	else
	{
		print_err("exit\n");
		print_err("คʕ • ₒ•ʔค ❤❤❤ exit: too many arguments\n");
		return (FALSE);
	}
	return (TRUE);
}
