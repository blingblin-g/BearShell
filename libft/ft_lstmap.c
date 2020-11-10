/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 01:26:15 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/18 17:39:31 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *head;

	head = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (new == 0)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
