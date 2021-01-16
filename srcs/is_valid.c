/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:35:48 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:50:40 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		valid_path(char *path)
{
	DIR		*directory;

	if ((directory = opendir(path)))
		return (closedir(directory));
	return (TRUE);
}

int		valid_first_command(char c)
{
	if (ft_strchr("|;", c))
		return (ERROR);
	return (SUCCESS);
}

int		valid_pipe(t_list *pipe_lst)
{
	while (pipe_lst)
	{
		if (find_multi_redir(pipe_lst->content) == ERROR)
			return (ERROR);
		if (valid_first_command(((char *)pipe_lst->content)[0]) == ERROR)
			return (ERROR);
		pipe_lst = pipe_lst->next;
	}
	return (SUCCESS);
}

int		is_valid_line(char **line)
{
	char	*new_line;

	new_line = ft_strtrim(*line, " ");
	free(*line);
	if (!ft_strcmp(new_line, ""))
	{
		free(new_line);
		return (ERROR);
	}
	if (new_line[0] == ';' || new_line[0] == '|' ||
			check_continuous(new_line) == ERROR)
	{
		free(new_line);
		print_error(PARSING_ERR, NULL);
		return (ERROR);
	}
	*line = new_line;
	return (SUCCESS);
}
