#include "mini.h"

void	concat_prolst(t_parse *pars, char *line, size_t i, int type)
{
	add_back_prolst(&pars->pro_lst, new_prolst(ft_substr(line, pars->start, i - pars->start), type));
	pars->start = i + 1;
}

void	parsing_loop(t_parse *pars, char *line, size_t i, int type)
{
	if (!pars->single_q && !pars->double_q)
	{
		if (i == 0 || (i != 0 && line[i - 1] != '\\'))
		{
			if ((type = is_semi_char(line[i])))
				concat_prolst(pars, line, i, type);
			is_quotes_true(line[i], pars);
		}
	}
	else
		is_quotes_false(line, i, pars);
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
		parsing_loop(pars, line, i, type);
		i++;
	}
	if (pars->single_q || pars->double_q)
		return (ERROR);
	if (i != pars->start)
		concat_prolst(pars, line, i, type);
	pro_lst = pars->pro_lst;
	return (make_pipe_lst(pro_lst, pars));
}

