#include "mini.h"


int		input_pipe_lst(t_parse *pars, char *raw, t_list **raw_lst)
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
				if ((type = is_pipe_char(raw[i])))
				{
					if (i != pars->start)
					{
						tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
						ft_lstadd_back(raw_lst, tmp_lst);
					}
					if (raw[i + 1] != 0 && raw[i + 1] == '|') // 이건 당연한거 아닌가?
						return (ERROR);
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
			if (i != 0 && pars->single_q && raw[i - 1] != '\\' && raw[i] == '\'')
				pars->single_q = FALSE;
			else if (i != 0 && pars->double_q && raw[i - 1] != '\\' && raw[i] == '\"')
				pars->double_q = FALSE;
		}
		i++;
	}
	// fprintf(stderr, "tmp_lst22: [%s], i - pars->start: [%lu]\n", tmp_lst->content, i - pars->start);
	if (i == pars->start)
	{
		return (ERROR);
	}
	tmp_lst = new_lst_trim(ft_substr(raw, pars->start, i - pars->start));
	ft_lstadd_back(raw_lst, tmp_lst);
	if (pars->single_q || pars->double_q)
	{
		return (ERROR);
	}
	return (SUCCESS);
}


int		main_parse(char *line, t_parse *pars)
{
	int		type;
	size_t	i;
	t_pro	*pro_lst;

	i = 0;
	pars->start = 0;
	type = 0;

	if (line == NULL)
		return (ERROR);
	while (line[i])
	{
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && line[i - 1] != '\\'))
			{
				if ((type = is_semi_char(line[i])))
				{
					pro_lst = new_prolst(ft_substr(line, pars->start, i - pars->start), type);
					add_back_prolst(&pars->pro_lst, pro_lst);
					pars->start = i + 1;
				}
				if (line[i] == '\"')
					pars->double_q = TRUE;
				else if (line[i] == '\'')
					pars->single_q = TRUE;
			}
		}
		else
		{
			if (i != 0 && pars->single_q && line[i - 1] != '\\' && line[i] == '\'')
				pars->single_q = FALSE;
			else if (i != 0 && pars->double_q && line[i - 1] != '\\' && line[i] == '\"')
				pars->double_q = FALSE;
		}
		i++;
	}
	if (pars->single_q || pars->double_q)
	{
		return (ERROR);
	}
	// if (i == pars->start)
	// {
	// 	return (ERROR);
	// }
	pro_lst = new_prolst(ft_substr(line, pars->start, i - pars->start), type);
	add_back_prolst(&pars->pro_lst, pro_lst);
	pro_lst = pars->pro_lst;

	while (pro_lst)
	{
		pro_lst->raw = free_strtrim(&pro_lst->raw, " ");
		if (input_pipe_lst(pars, pro_lst->raw, &pro_lst->pipe_lst) == ERROR) // free도 다 해줘야함
			return (ERROR);
		pro_lst = pro_lst->next;
	}
	pro_lst = pars->pro_lst;
	// if (valid_command(((char *)pro_lst->pipe_lst->content)[0]) == ERROR)
	// {
	// 	return (ERROR);
	// }
	if (valid_pipe(pro_lst->pipe_lst) == ERROR)
	{
		return (ERROR);
	}
	return (SUCCESS);
}

