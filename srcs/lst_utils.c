/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:25:42 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:26:07 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*new_lst_trim(char *content)
{
	t_list	*tmp_lst;

	content = free_strtrim(&content, " ");
	tmp_lst = ft_lstnew(content);
	return (tmp_lst);
}

void	add_redirection_lst(t_parse *pars, t_list **lst, int type)
{
	char	*str;

	str = NULL;
	if (type == INPUT || type == OUTPUT || type == APPEND)
		pars->fd_count++;
	if (type == INPUT)
		str = ft_strdup("<");
	else if (type == OUTPUT)
		str = ft_strdup(">");
	else if (type == APPEND)
		str = ft_strdup(">>");
	if (str)
		ft_lstadd_back(lst, ft_lstnew(str));
}
