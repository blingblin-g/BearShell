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
		return (ERROR);
	return (SUCCESS);
}

int		valid_pipe(t_list *pipe_lst)
{
	while (pipe_lst)
	{
		if (valid_command(((char *)pipe_lst->content)[0]) == ERROR)
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
	if (new_line[0] == ';')
	{
		free(new_line);
		print_error(PARSING_ERR, NULL);
		return (ERROR);
	}
	*line = new_line;
	return (SUCCESS);
}