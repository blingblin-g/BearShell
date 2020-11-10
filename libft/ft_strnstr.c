/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:41:00 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 18:37:40 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*l;
	size_t	i;
	size_t	j;

	i = 0;
	b = (char *)big;
	l = (char *)little;
	if (l[0] == 0)
		return (b);
	else
	{
		while (b[i] != 0 && i < len)
		{
			j = 0;
			while (b[i + j] == l[j] && (i + j < len))
			{
				if (l[j + 1] == 0)
					return (&b[i]);
				j++;
			}
			i++;
		}
		return (0);
	}
}
