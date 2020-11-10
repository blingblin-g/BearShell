/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 20:40:05 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 18:28:42 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t			i;
	size_t			slen;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	slen = ft_strlen((const char *)s);
	if (size == 0)
		return (slen);
	else
	{
		while (s[i] && (i + 1 < size))
		{
			d[i] = s[i];
			++i;
		}
		d[i] = 0;
		return (slen);
	}
}
