#include "mini.h"

void	redir_iter(size_t *i, t_parse *pars, char *raw, t_list **raw_lst)
{
	if (!pars->single_q && !pars->double_q)
	{
		if (*i == 0 || (*i != 0 && raw[*i - 1] != '\\'))
		{
			if ((pars->type = is_redirection_char(raw[*i])))
			{
				if (*i != pars->start)
					substr_addlst_back(raw_lst, raw, pars->start, *i);
				if (pars->type == OUTPUT && raw[*i + 1] && raw[*i + 1] == '>')
				{
					(*i)++;
					pars->type = APPEND;
				}
				add_redirection_lst(pars, raw_lst, pars->type);
				pars->start = *i + 1;
			}
			is_quotes_true(raw[*i], pars);
		}
	}
	else
		is_quotes_false(raw, *i, pars);
}

int		redir_ret(size_t i, t_parse *pars, char *raw, t_list **raw_lst)
{
	if (i == pars->start)
		return (ERROR);
	substr_addlst_back(raw_lst, raw, pars->start, i);
	if (pars->single_q || pars->double_q)
	{
		print_error(PARSING_ERR, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

int		input_redirection_lst(t_parse *pars, char *raw, t_list **raw_lst)
{
	size_t	i;

	i = 0;
	pars->start = i;
	pars->type = 0;
	while (raw[i])
	{ 
		redir_iter(&i, pars, raw, raw_lst);
		i++;
	}
	return (redir_ret(i, pars, raw, raw_lst));
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
	{
		ft_lstclear(&redir_lst, free);
		return (ERROR);
	}
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