/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:35:20 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:48:06 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		make_pipe_lst_iter(size_t i, t_parse *pars, char *raw, t_list **raw_lst)
{
	if (!pars->single_q && !pars->double_q)
	{
		if (i == 0 || (i != 0 && raw[i - 1] != '\\'))
		{
			if ((pars->type = is_pipe_char(raw[i])))
			{
				if (i != pars->start)
					substr_addlst_back(raw_lst, raw, pars->start, i);
				if (raw[i + 1] == '|')
					return (ERROR);
				pars->start = i + 1;
			}
			is_quotes_true(raw[i], pars);
		}
	}
	else
		is_quotes_false(raw, i, pars);
	return (SUCCESS);
}

int		make_pipe_lst(t_pro *pro_lst, t_parse *pars)
{
	while (pro_lst)
	{
		pro_lst->raw = free_strtrim(&pro_lst->raw, " ");
		if (input_pipe_lst(pars, pro_lst->raw, &pro_lst->pipe_lst) == ERROR)
			return (ERROR);
		pro_lst = pro_lst->next;
	}
	pro_lst = pars->pro_lst;
	if (valid_pipe(pro_lst->pipe_lst) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	substr_addlst_back(t_list **raw_lst, char *raw, int start, int i)
{
	ft_lstadd_back(raw_lst, new_lst_trim(ft_substr(raw, start, i - start)));
}

int		input_pipe_lst(t_parse *pars, char *raw, t_list **raw_lst)
{
	size_t	i;

	i = 0;
	pars->start = i;
	pars->type = 0;
	while (raw[i])
	{
		if (make_pipe_lst_iter(i, pars, raw, raw_lst) == ERROR)
			return (ERROR);
		i++;
	}
	if (i == pars->start)
		return (ERROR);
	substr_addlst_back(raw_lst, raw, pars->start, i);
	if (pars->single_q || pars->double_q)
		return (ERROR);
	return (SUCCESS);
}
