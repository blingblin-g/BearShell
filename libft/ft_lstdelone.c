/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:08:00 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/18 17:35:06 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	del(lst->content);
// 	free(lst);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != 0)
	{
		del(lst->content);
		if (lst->next != 0)
		{
			lst->content = lst->next->content;
			lst->next = lst->next->next;
		}
	}
}