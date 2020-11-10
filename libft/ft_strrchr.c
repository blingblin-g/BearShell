/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 20:22:45 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 18:39:44 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	int		len;

	ret = (char *)s;
	len = ft_strlen(ret);
	while (len >= 0)
	{
		if (ret[len] == c)
			return (&ret[len]);
		else
			--len;
	}
	if (c == 0)
		return (&ret[len]);
	else
		return (0);
}
