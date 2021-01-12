#include "mini.h"

void	get_fd_count(t_list	*redir_lst, t_exec *exec_info)
{
	exec_info->input_count = 0;
	exec_info->output_count = 0;
	while (redir_lst)
	{
		if (redir_lst->content)
		{
			if (((char *)redir_lst->content)[0] == '>')
				exec_info->output_count++;
			if (((char *)redir_lst->content)[0] == '<')
				exec_info->input_count++;
		}
		redir_lst = redir_lst->next;
	}
}

int		create_fds(t_exec *exec_info, char *redir_str, char *file_str)
{
	int	fd;

	fd = 0;
	if (!ft_strncmp(file_str, ">", 2) || !ft_strncmp(file_str, ">>", 3) ||
		!ft_strncmp(file_str, "<", 2))
		return (ERROR);
	if (!ft_strcmp(redir_str, ">"))
	{
		fd = open(file_str, O_RDWR | O_TRUNC | O_CREAT, 00777);
		exec_info->fd[1][exec_info->fd_output_idx++] = fd;
	}
	else if (!ft_strcmp(redir_str, ">>"))
	{
		fd = open(file_str, O_RDWR | O_APPEND | O_CREAT, 00777);
		exec_info->fd[1][exec_info->fd_output_idx++] = fd;
	}
	else if (!ft_strcmp(redir_str, "<"))
	{
		fd = open(file_str, O_RDONLY, 00777);
		exec_info->fd[0][exec_info->fd_input_idx++] = fd;
	}
	free(redir_str);
	free(file_str);
	if (fd < 0)
		return (ERROR);
	return (SUCCESS);
}

void	close_fds(t_exec *exec_info)
{
	int		i;

	i = 0;
	if (exec_info->fd[0])
	{
		dup2(exec_info->std[0], 0);
		close(exec_info->std[0]);
		while (i < exec_info->input_count)
		{
			close(exec_info->fd[0][i]);
			i++;
		}
	}
	i = 0;
	if (exec_info->fd[1])
	{
		dup2(exec_info->std[1], 1);
		close(exec_info->std[1]);
		while (i < exec_info->output_count)
		{
			close(exec_info->fd[1][i]);
			i++;
		}
	}
}