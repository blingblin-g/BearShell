/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:35:02 by chlim             #+#    #+#             */
/*   Updated: 2021/01/18 00:45:46 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		init_exec(t_exec *exec_info, int lst_count)
{
	int		fd_count;

	fd_count = exec_info->input_count + exec_info->output_count;
	if (exec_info->input_count > 0)
		if (!(exec_info->fd[0] = (int *)malloc(sizeof(int) *
						(exec_info->input_count))))
			return (ERROR);
	if (exec_info->output_count > 0)
		if (!(exec_info->fd[1] = (int *)malloc(sizeof(int) *
						(exec_info->output_count))))
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

int		create_exec_iter(t_parse *pars, t_exec *exec_info, t_list **redir_lst)
{
	char	*res;

	res = process_quotes(pars, (*redir_lst)->content);
	if (res == ERROR)
		return (ERROR);
	if (res && (((char *)(*redir_lst)->content)[0] == '>' ||
			((char *)(*redir_lst)->content)[0] == '<'))
	{
		if ((*redir_lst)->next)
			if (create_fds(exec_info, res, process_quotes(
							pars, (*redir_lst)->next->content)) == ERROR)
				return (ERROR);
		*redir_lst = (*redir_lst)->next;
	}
	if (!is_redir(res))
	{
		exec_info->argv[exec_info->argv_idx] = res;
		exec_info->argv_idx++;
	}
	else
		free(res);
	if ((*redir_lst))
		*redir_lst = (*redir_lst)->next;
	return (SUCCESS);
}

t_exec	*create_exec(t_parse *pars, t_list *redir_lst)
{
	t_exec	*exec_info;
	int		lst_count;

	if (!(exec_info = (t_exec *)malloc(sizeof(t_exec))))
		return (ERROR);
	lst_count = ft_lstsize(redir_lst);
	get_fd_count(redir_lst, exec_info);
	init_exec(exec_info, lst_count);
	while (redir_lst)
	{
		if (create_exec_iter(pars, exec_info, &redir_lst) == ERROR)
		{
			free_exec_info(&exec_info);
			return (ERROR);
		}
	}
	return (exec_info);
}
