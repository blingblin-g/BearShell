/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:26:31 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:26:45 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		search_quotes(char c, char *line, int i)
{
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (ERROR);
}
