/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:27:01 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:28:59 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	process_single_quotes(t_parse *pars,
		char *content, char **result, size_t *i)
{
	*result = free_join(*result,
			out_of_quotes_zone(content, &(pars->start), i));
	*result = free_join(*result,
			get_single_quote_zone(content, &(pars->start), i));
	pars->single_q = FALSE;
}

void	process_double_quotes(t_parse *pars,
		char *content, char **result, size_t *i)
{
	*result = free_join(*result,
			out_of_quotes_zone(content, &(pars->start), i));
	*result = free_join(*result,
			get_double_quote_zone(content, &(pars->start), i));
	pars->double_q = FALSE;
}

void	process_quotes_iter(t_parse *pars,
		char *content, char **result, size_t *i)
{
	if (!pars->single_q && !pars->double_q)
	{
		if (*i == 0 || (*i != 0 && content[*i - 1] != '\\'))
		{
			if (content[*i] == '\"')
				pars->double_q = TRUE;
			else if (content[*i] == '\'')
				pars->single_q = TRUE;
		}
		if (!content[*i])
			*result = free_join(*result,
				out_of_quotes_zone(content, &(pars->start), i));
	}
	if (pars->single_q)
		process_single_quotes(pars, content, result, i);
	if (pars->double_q)
		process_double_quotes(pars, content, result, i);
	(*i)++;
}

char	*process_quotes(t_parse *pars, char *content)
{
	size_t	i;
	char	*result;

	i = 0;
	pars->single_q = FALSE;
	pars->double_q = FALSE;
	pars->start = 0;
	result = ft_strdup("");
	content = process_home(ft_strdup(content));
	while (i <= ft_strlen(content))
		process_quotes_iter(pars, content, &result, &i);
	if (pars->single_q || pars->double_q)
		return (ERROR);
	free(content);
	return (result);
}
