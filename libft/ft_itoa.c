/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 02:24:13 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/22 00:35:51 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len = 1;
		if (n == -2147483648)
		{
			len++;
			n = n / 10;
		}
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*build_malloc(int len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == 0 || len == 0)
		return (0);
	result[len] = 0;
	return (result);
}

void		just_iterate(int n, char *result, int len)
{
	while (n > 0)
	{
		result[len - 1] = n % 10 + '0';
		n = n / 10;
		--len;
	}
}

char		*ft_itoa(int n)
{
	int		len;
	char	*result;

	len = count_len(n);
	if (!(result = build_malloc(len)))
		return (0);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			result[len - 1] = 8 + '0';
			n = n / 10;
			--len;
		}
		n = -n;
		result[0] = '-';
	}
	else if (n == 0)
		result[len - 1] = '0';
	just_iterate(n, result, len);
	return (result);
}
