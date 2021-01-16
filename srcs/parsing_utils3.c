/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:34:42 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:42:06 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	process_sayeon(char c, char **result)
{
	if (c == '?')
		*result = free_join(*result, ft_itoa(get_info()->exit_status >> 8));
	if (c == '$')
		*result = free_join(*result, ft_itoa(get_info()->pid));
	if (c == '-')
		*result = free_join(*result, ft_strdup("himBH"));
	if ((c > '0' && c <= '9') || c == '!' || c == '@' || c == '*')
		;
	if (c == '0')
		*result = free_join(*result, ft_strdup("minishell"));
	if (c == '#')
		*result = free_join(*result, ft_strdup("0"));
}

char	*find_var_name(char *content, size_t *i)
{
	size_t	start;

	start = *i;
	while (!how2divide(content[*i]))
		(*i)++;
	return (ft_substr(content, start, *i - start));
}

char	*process_home(char *content)
{
	char	*temp;
	char	*home_path;

	if ((content)[0] == '~')
	{
		if ((content)[1] == '/' || (content)[1] == '\0')
		{
			home_path = get_env_item("HOME");
			temp = ft_strjoin(home_path, (content) + 1);
			free(home_path);
			free(content);
			content = temp;
		}
	}
	return (content);
}

void	is_quotes_true(char c, t_parse *pars)
{
	if (c == '\"')
		pars->double_q = TRUE;
	else if (c == '\'')
		pars->single_q = TRUE;
}

void	is_quotes_false(char *line, size_t i, t_parse *pars)
{
	if (i != 0 && pars->single_q && line[i] == '\'')
		pars->single_q = FALSE;
	else if (i != 0 && pars->double_q && line[i - 1] != '\\' && line[i] == '\"')
		pars->double_q = FALSE;
}
