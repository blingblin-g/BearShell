#include "mini.h"

int	main_parse(char *line)
{
	int		i;
	t_parse	pars;

	i = 0;
	while (line[i])
	{
		if (!pars.single_q && !pars.double_q)
		{
			if (i == 0 || (i != 0 && line[i - 1] != '\\'))
			{
				if (line[i] == '\"')
				{
					pars.double_q = TRUE;
					printf("pars.double_q = TRUE [%d]\n", i);
				}
				else if (line[i] == '\'')
				{
					pars.single_q = TRUE;
					printf("pars.single_q = TRUE [%d]\n", i);
				}
			}
		}
		else
		{
			if (i != 0 && pars.single_q && line[i - 1] != '\\' && line[i] == '\'')
			{
				pars.single_q = FALSE;
				printf("pars.single_q = FALSE [%d]\n", i);
			}
			else if (i != 0 && pars.double_q && line[i - 1] != '\\' && line[i] == '\"')
			{
				pars.double_q = FALSE;
				printf("pars.double_q = FALSE; [%d]\n", i);
			}
		}
		i++;
	}
	return (0);
}