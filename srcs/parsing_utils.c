#include "mini.h"

int		is_semi_char(char c)
{
	if (c == ';')
		return (SEMI);
	if (c == 0)
		return (END);
	return (0);
}

int		is_pipe_char(char c)
{
	if (c == '|')
		return (PIPE);
	return (0);
}

int		is_redirection_char(char c)
{
	if (c == '>')
		return (OUTPUT);
	if (c == '<')
		return (INPUT);
	if (c == ' ')
		return (SPACE);
	return (0);
}

void	init_pars(t_parse *pars)
{
	pars->single_q = FALSE;
	pars->double_q = FALSE;
	pars->pro_lst = NULL;
	pars->line = NULL;
	pars->is_space = FALSE;
	pars->start = 0;
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