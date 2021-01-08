/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 19:23:30 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/22 00:34:35 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*buf;
	unsigned int	slen;

	i = 0;
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_calloc(1, 1));
	buf = (char *)malloc(len + 1);
	buf[len] = 0;
	if (buf == 0)
		return (0);
	while (i < len)
	{
		buf[i] = s[start];
		++start;
		++i;
	}
	return (buf);
}
