/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:19:03 by sooyoon           #+#    #+#             */
/*   Updated: 2020/11/10 22:26:02 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*ret;

	ret = (char *)malloc(ft_strlen(s) + 1);
	if (ret == 0 || s == 0)
		return (0);
	ft_memcpy(ret, s, ft_strlen(s) + 1);
	return (ret);
}