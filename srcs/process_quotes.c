#include "mini.h"


char *process_quotes(t_parse *pars, char *content)
{
	size_t i;
	char *result;

	i = 0;
	pars->single_q = FALSE;
	pars->double_q = FALSE;
	pars->start = 0;
	result = ft_strdup("");
	content = process_home(ft_strdup(content));
	while (i <= ft_strlen(content))
	{
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && content[i - 1] != '\\'))
			{
				if (content[i] == '\"')
					pars->double_q = TRUE;
				else if (content[i] == '\'')
					pars->single_q = TRUE;
			}
			if (!content[i])
				result = free_join(result, out_of_quotes_zone(content, &(pars->start), &i));
		}
		if (pars->single_q)
		{
			result = free_join(result, out_of_quotes_zone(content, &(pars->start), &i));
			result = free_join(result, get_single_quote_zone(content, &(pars->start), &i));
			pars->single_q = FALSE;
		}
		if (pars->double_q)
		{
			result = free_join(result, out_of_quotes_zone(content, &(pars->start), &i));
			result = free_join(result, get_double_quote_zone(content, &(pars->start), &i));
			pars->double_q = FALSE;
		}
		i++;
	}
	if (pars->single_q || pars->double_q)
		return (ERROR);
	free(content);
	return (result);
}