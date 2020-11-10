/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 04:22:57 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 18:14:48 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*skip_word(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			break ;
		s++;
	}
	return (s);
}

static char		*skip_c(char *s, char c)
{
	while (*s)
	{
		if (*s != c)
			break ;
		s++;
	}
	return (s);
}

static size_t	ft_word_count(char *s, char c)
{
	int			count;

	count = 0;
	while (*s)
	{
		s = skip_c(s, c);
		if (*s == 0)
			break ;
		s = skip_word(s, c);
		count++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	char		**result;
	size_t		count;
	size_t		idx;
	char		*start;
	char		*finish;

	idx = 0;
	count = ft_word_count((char *)s, c);
	result = (char **)malloc((count + 1) * sizeof(char*));
	if (result == 0)
		return (0);
	start = (char *)s;
	while (idx < count)
	{
		start = skip_c(start, c);
		if (*start == 0)
			break ;
		finish = skip_word(start, c);
		result[idx] = ft_substr(start, 0, finish - start);
		start = finish;
		idx++;
	}
	result[idx] = 0;
	return (result);
}
