/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:21:55 by sooyoon           #+#    #+#             */
/*   Updated: 2020/11/10 22:22:08 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)ptr;
	while (i < num)
	{
		if (a[i] == (unsigned char)value)
			return (&a[i]);
		else
			++i;
	}
	return (0);
}