/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 03:33:01 by sooyoon           #+#    #+#             */
/*   Updated: 2020/04/20 18:41:53 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*start;
	char	*finish;
	int		len;
	int		i;

	i = 0;
	start = (char *)s1;
	len = ft_strlen(s1);
	finish = (char *)&s1[len];
	while (*start && ft_strchr(set, *start))
	{
		start++;
		i++;
	}
	while (ft_strrchr(set, *finish) && start < finish)
		finish--;
	result = ft_substr(s1, i, finish - start + 1);
	return (result);
}
