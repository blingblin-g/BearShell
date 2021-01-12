#include "mini.h"

int		 init_exec(t_exec	*exec_info, int lst_count)
{
	int		fd_count;


	fd_count = exec_info->input_count + exec_info->output_count;
	// printf("exec_info->input_count: [%d], exec_info->output_count: [%d]\n", exec_info->input_count, exec_info->output_count);
	if (exec_info->input_count > 0)
		if (!(exec_info->fd[0] = (int *)malloc(sizeof(int) * (exec_info->input_count))))
			return (ERROR);
	if (exec_info->output_count > 0)
		if (!(exec_info->fd[1] = (int *)malloc(sizeof(int) * (exec_info->output_count))))
			return (ERROR);
	if (exec_info->input_count <= 0)
		exec_info->fd[0] = NULL;
	if (exec_info->output_count <= 0)
		exec_info->fd[1] = NULL;
	if (!(exec_info->argv = (char **)calloc(sizeof(char *),
		(lst_count - fd_count + 1))))
		return (ERROR);
	exec_info->fd_input_idx = 0;
	exec_info->fd_output_idx = 0;
	exec_info->argv_idx = 0;
	return (SUCCESS);
}


t_exec	*create_exec(t_parse *pars, t_list *redir_lst)
{
	t_exec	*exec_info;
	char	*res;
	int		lst_count;

	if (!(exec_info = (t_exec *)malloc(sizeof(t_exec))))
		return (NULL);
	lst_count = ft_lstsize(redir_lst);
	get_fd_count(redir_lst, exec_info);
	init_exec(exec_info, lst_count);
	while (redir_lst)
	{
		res = process_quotes(pars, ft_strdup(redir_lst->content));
		if (res && (res[0] == '>' || res[0] == '<'))
		{
			if (redir_lst->next)
				if (create_fds(exec_info, res, process_quotes(pars, ft_strdup(redir_lst->next->content))) == ERROR)
					return (ERROR);
			redir_lst = redir_lst->next;
		}
		else if (ft_strcmp(res, ""))
		{
			exec_info->argv[exec_info->argv_idx] = res;
			exec_info->argv_idx++;
		}
		if (redir_lst)
			redir_lst = redir_lst->next;
	}
	return (exec_info);
}
