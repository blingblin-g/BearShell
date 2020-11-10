/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:13:29 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/27 00:12:44 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr(n / 10, fd);
		ft_putchar('8', fd);
	}
	else if (n < 0)
	{
		ft_putchar('-', fd);
		ft_putnbr(-n, fd);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, fd);
		ft_putchar('0' + n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr(n, fd);
}
