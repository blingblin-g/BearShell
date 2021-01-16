/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:36:11 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:36:12 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		is_redir_pipe(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (TRUE);
	return (FALSE);
}

int		find_multi_redir(char *text)
{
	size_t	size;

	size = ft_strlen(text);
	if (ft_strnstr(text, ">>>", size))
		return (ERROR);
	if (ft_strnstr(text, "<<<", size))
		return (ERROR);
	return (SUCCESS);
}

int		check_continuous(char *str)
{
	int		space_trigger;
	char	prev_ch;

	space_trigger = FALSE;
	prev_ch = ' ';
	while (*str)
	{
		while ((*str >= 9 && *str <= 13) || *str == 32)
		{
			++str;
			space_trigger = TRUE;
		}
		if (is_redir_pipe(*str))
		{
			if (space_trigger && is_redir_pipe(prev_ch))
				return (ERROR);
			else if (is_redir_pipe(prev_ch) && prev_ch != *str)
				return (ERROR);
			space_trigger = FALSE;
		}
		prev_ch = *str;
		str++;
	}
	return (SUCCESS);
}
