/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:11:35 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/18 17:33:33 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {
// 	t_list *daum;

// 	while (*lst)
// 	{
// 		daum = (*lst)->next;
// 		ft_lstdelone(*lst, del);
// 		*lst = daum;
// 	}
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*remove_node;

	if (lst != 0)
	{
		node = *lst;
		while (node != 0)
		{
			remove_node = node;
			node = node->next;
			del(remove_node->content);
			free(remove_node);
		}
		*lst = 0;
	}
}