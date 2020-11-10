/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:06:02 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 19:09:16 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)s;
	while (ret[i])
	{
		if (ret[i] == c)
			return (&ret[i]);
		else
			++i;
	}
	if (c == 0)
		return (&ret[i]);
	else
		return (0);
}
