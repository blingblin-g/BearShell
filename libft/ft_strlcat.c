/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:39:53 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 18:25:43 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char			*d;
	char			*s;
	unsigned int	n;
	unsigned int	dest_len;

	d = (char *)dst;
	s = (char *)src;
	n = size;
	while (n-- != 0 && *d != 0)
		d++;
	dest_len = d - (char *)dst;
	n = size - dest_len;
	if (n == 0)
		return (dest_len + ft_strlen(s));
	while (*s != 0)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = 0;
	return (dest_len + (s - src));
}
