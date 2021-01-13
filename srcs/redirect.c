#include "mini.h"

int		input_redirection_lst(t_parse *pars, char *raw, t_list **raw_lst)
{
	t_list	*tmp_lst;
	size_t	i;
	int		type;

	i = 0;
	pars->start = i;
	type = 0;
	while (raw[i])
	{ 
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && raw[i - 1] != '\\'))
			{
				if ((type = is_redirection_char(raw[i])))
				{
					if (i != pars->start)
					{
						tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
						ft_lstadd_back(raw_lst, tmp_lst);
					}
					if (type == OUTPUT && raw[i + 1] && raw[i + 1] == '>')
					{
						i++;
						type = APPEND;
					}
					add_redirection_lst(pars, raw_lst, type);
					pars->start = i + 1;
				}
				if (raw[i] == '\"')
					pars->double_q = TRUE;
				else if (raw[i] == '\'')
					pars->single_q = TRUE;
			}
		}
		else
		{
			if (i != 0 && pars->single_q && raw[i] == '\'')
				pars->single_q = FALSE;
			else if (i != 0 && pars->double_q && raw[i - 1] != '\\' && raw[i] == '\"')
				pars->double_q = FALSE;
		}
		i++;
	}

	if (i == pars->start)
	{
		return (ERROR);
	}
	tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
	ft_lstadd_back(raw_lst, tmp_lst);
	if (pars->single_q || pars->double_q)
	{
		print_error(PARSING_ERR, NULL); // free 해줘야함
		return (ERROR);
	}
	return (SUCCESS);
}

t_exec	*redir_process(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info = NULL;
	t_list	*redir_lst = NULL;

	if (input_redirection_lst(pars, pipe_lst->content, &redir_lst) != ERROR)
	{
		if ((exec_info = create_exec(pars, redir_lst)) == ERROR)
		{
			ft_lstclear(&redir_lst, free);
			free(redir_lst);
			return (ERROR);
		}
		if (redir_lst != NULL)
		{
			ft_lstclear(&redir_lst, free);
			free(redir_lst);
		}
	}
	else
		return (ERROR);
	if (exec_info->fd[0] != NULL && exec_info->fd[0][exec_info->input_count - 1] != 0)
	{
		exec_info->std[0] = dup(0);
		dup2(exec_info->fd[0][exec_info->input_count - 1], 0);
	}
	if (exec_info->fd[1] != NULL && exec_info->fd[1][exec_info->output_count - 1] != 0)
	{
		exec_info->std[1] = dup(1);
		dup2(exec_info->fd[1][exec_info->output_count - 1], 1); 
	}
	return (exec_info);
}