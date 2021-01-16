/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:34:49 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:43:43 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	process_dollar(char **result, char *content, size_t *start, size_t *i)
{
	char	*var_name;

	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = ++(*i);
	if (is_sayeon(content[*i]))
	{
		process_sayeon(content[*i], result);
		*start = *i + 1;
	}
	else if (how2divide(content[*i]))
	{
		*result = free_join(*result, ft_strdup("$"));
		(*i)--;
	}
	else
	{
		var_name = find_var_name(content, i);
		*result = free_join(*result, get_env_item(var_name));
		free(var_name);
		*start = (*i)--;
	}
}

char	*get_single_quote_zone(char *content, size_t *start, size_t *i)
{
	char	*result;

	(*i)++;
	*start = *i;
	result = ft_strdup("");
	while (*i <= ft_strlen(content))
	{
		if (!content[*i])
			return (NULL);
		else if (content[*i] == '\'')
		{
			fill_result_plus_start(&result, content, start, i);
			break ;
		}
		(*i)++;
	}
	return (result);
}

char	*get_double_quote_zone(char *content, size_t *start, size_t *i)
{
	char	*result;

	*start = ++(*i);
	result = ft_strdup("");
	while (*i <= ft_strlen(content))
	{
		if (!content[*i])
			return (NULL);
		if (content[*i] == '\\')
		{
			fill_result(&result, content, start, i);
			if (is_escape(content[*i + 1]))
				*start = ++(*i);
		}
		else if (content[*i] == '$')
			process_dollar(&result, content, start, i);
		else if (content[*i] == '\"')
		{
			fill_result_plus_start(&result, content, start, i);
			break ;
		}
		(*i)++;
	}
	return (result);
}

char	*out_of_quotes_zone(char *content, size_t *i, size_t *end_i)
{
	char	*result;
	size_t	start;

	start = *i;
	result = ft_strdup("");
	while (*i <= *end_i)
	{
		if (content[*i] == '\\')
			fill_result_plus_i(&result, content, &start, i);
		else if (content[*i] == '$')
			process_dollar(&result, content, &start, i);
		else if (is_outofquote_end(content[*i]))
		{
			fill_result_plus_start(&result, content, &start, i);
			break ;
		}
		(*i)++;
	}
	return (result);
}
