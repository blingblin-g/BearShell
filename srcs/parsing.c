#include "mini.h"

int		is_special_char(char c)
{
	if (c == '|')
		return (PIPE);
	// if (c == '>')
	// 	return (OUTPUT);
	// if (c == '<')
	// 	return (INPUT);
	if (c == ';')
		return (SEMI);
	if (c == 0)
		return (END);
	return 0;
}

void	input_content(t_pro *pro_lst, char *line, int i, int start)
{
	char	**tmp;

	tmp = (char **)&ft_lstlast(pro_lst->raw_lst)->content;
	*tmp = free_join(*tmp, ft_substr(line, start, i - start));
	*tmp = free_strtrim(tmp, " ");
}

int		search_quotes(char c, char *line, int i) // return index of pair_quotes
{
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (ERROR); // 다 돌았지만 못찾은거임. 즉 pair quote가 없는 것
}

int		input_raw_lst(t_parse *pars, t_pro *pro_lst)
{
	int		start;
	char	*line;
	size_t	i;

	i = 0;
	start = i;
	line = pro_lst->raw;
	while (line[i])
	{
		if (!pars->single_q && !pars->double_q)
		{
			while (line[i] == ' ')
			{
				i++;
				pars->is_space = TRUE;
			}
			if (i >= ft_strlen(line) - 1)
			{
				i = ft_strlen(line);
				input_content(pro_lst, line, i, start);
				break ;
			}
			if (pars->is_space)
			{
				input_content(pro_lst, line, i, start);
				ft_lstadd_back(&pro_lst->raw_lst, ft_lstnew(ft_strdup("")));
				pars->is_space = FALSE;
				start = i;
			}
			if (i == 0 || (i != 0 && line[i - 1] != '\\'))
			{
				if (line[i] == '\"')
				{
					input_content(pro_lst, line, i, start);
					pars->double_q = TRUE;
					start = i;
				}
				else if (line[i] == '\'')
				{
					input_content(pro_lst, line, i, start);
					pars->single_q = TRUE;
					start = i;
				}
			}
		}
		else
		{
			if (i != 0 && pars->single_q && line[i - 1] != '\\' && line[i] == '\'')
			{
				pars->single_q = FALSE;
			}
			else if (i != 0 && pars->double_q && line[i - 1] != '\\' && line[i] == '\"')
			{
				pars->double_q = FALSE;
			}
		}
		i++;
	}
	if (pars->single_q || pars->double_q)
		return (ERROR);
	return (SUCCESS);
}

int	main_parse(char *line, t_parse *pars)
{
	int		type;
	int		i;
	t_pro	*pro_lst;
	// t_list	*raw_lst;

	i = 0;
	pars->start = 0;
	type = 0;
	while (line[i])
	{
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && line[i - 1] != '\\'))
			{
				if ((type = is_special_char(line[i])))
				{
					pro_lst = new_prolst(ft_substr(line, pars->start, i - pars->start), type);
					// if (type == OUTPUT && line[i] && line[i + 1] == '>')
					// {
					// 	pro_lst->type = APPEND;
					// 	i++;
					// }
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
	pro_lst = new_prolst(ft_substr(line, pars->start, i - pars->start), type);
	add_back_prolst(&pars->pro_lst, pro_lst);
	pro_lst = pars->pro_lst;
	while (pro_lst)
	{
		pro_lst->raw = free_strtrim(&pro_lst->raw, " ");
		input_raw_lst(pars, pro_lst);
		pro_lst = pro_lst->next;
	}
	pro_lst = pars->pro_lst;
	// while (pro_lst)
	// {
	// 	raw_lst = pro_lst->raw_lst;
	// 	while (raw_lst)
	// 	{
	// 		char	*after_parsing = process_quotes(pars, raw_lst->content);
	// 		ft_lstadd_back(&(pro_lst->cmd_lst), ft_lstnew(after_parsing));
	// 		raw_lst = raw_lst->next;
	// 	}
	// 	pro_lst = pro_lst->next;
	// }
	print_prolst(pars->pro_lst); // only 4 test
	return (0);
}

