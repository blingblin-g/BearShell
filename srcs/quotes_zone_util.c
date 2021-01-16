/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_zone_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlim <chlim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:35:34 by chlim             #+#    #+#             */
/*   Updated: 2021/01/16 21:48:42 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	fill_result(char **result, char *content, size_t *start, size_t *i)
{
	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = *i;
}

void	fill_result_plus_start(char **result, char *content,
		size_t *start, size_t *i)
{
	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = *i + 1;
}

void	fill_result_plus_i(char **result, char *content,
		size_t *start, size_t *i)
{
	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = ++(*i);
}
