/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:31:41 by chlim             #+#    #+#             */
/*   Updated: 2021/01/17 20:34:15 by sooyoon          ###   ########.fr       */
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
	int		is_free;

	is_free = FALSE;
	if (path == 0)
	{
		path = get_env_item("HOME");
		is_free = TRUE;
	}
	else if (valid_path(path))
	{
		get_info()->exit_status = 1 << 8;
		if (!is_free)
			path = ft_strdup(path);
		return (print_error(PATH_ERR, path));
	}
	result = !chdir(path);
	if (!result)
		get_info()->exit_status = 0;
	else
		get_info()->exit_status = 1 << 8;
	if (is_free)
		free(path);
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

int		is_only_num(char *str)
{
	if (str[0] == '+' || str[0] == '-')
		str++;
	if (*str == 0)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int		builtin_exit(char **argv)
{
	size_t	size;

	size = len(argv);
	print_err("exit\n");
	if (size == 1)
		exit(get_info()->exit_status);
	else if (size == 2)
	{
		if (is_only_num(argv[1]) == FALSE)
		{
			print_err("คʕ • ₒ•ʔค ❤❤❤ exit: numeric argument required\n");
			exit(255);
		}
		else
			exit((unsigned char)ft_atoi(argv[1]));
	}
	else
	{
		print_err("คʕ • ₒ•ʔค ❤❤❤ exit: too many arguments\n");
		return (FALSE);
	}
	return (TRUE);
}
