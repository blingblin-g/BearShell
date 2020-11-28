#include "mini.h"

int		is_special_char(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (OUTPUT);
	if (c == '<')
		return (INPUT);
	if (c == ';')
		return (SEMI);
	if (c == 0)
		return (END);
	return 0;
}

int	main_parse(char *line)
{
	int		type;
	int		i;
	t_parse	pars;
	t_pro	*pro_lst;

	i = 0;
	pars.start = 0;
	type = 0;
	while (line[i])
	{
		if (!pars.single_q && !pars.double_q)
		{
			if ((type = is_special_char(line[i])))
			{
				pro_lst = new_prolst(ft_substr(line, pars.start, i - pars.start), type);
				if (type == OUTPUT && line[i] && line[i + 1] == '>')
				{
					type = APPEND;
					pro_lst->type = type;
					i++;
				}
				add_back_prolst(&pars.pro_lst, pro_lst);
				pars.start = i + 1;
			}
			if (i == 0 || (i != 0 && line[i - 1] != '\\'))
			{
				if (line[i] == '\"')
					pars.double_q = TRUE;
				else if (line[i] == '\'')
					pars.single_q = TRUE;
			}
		}
		else
		{
			if (i != 0 && pars.single_q && line[i - 1] != '\\' && line[i] == '\'')
				pars.single_q = FALSE;
			else if (i != 0 && pars.double_q && line[i - 1] != '\\' && line[i] == '\"')
				pars.double_q = FALSE;
		}
		i++;
	}
	pro_lst = new_prolst(ft_substr(line, pars.start, i - pars.start), type);
	add_back_prolst(&pars.pro_lst, pro_lst);
	print_prolst(pars.pro_lst);
	return (0);
}