/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:30:55 by chlim             #+#    #+#             */
/*   Updated: 2021/01/18 02:19:50 by chlim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		env(void)
{
	t_list	*tmp;

	tmp = get_info()->env_list;
	while (tmp)
	{
		if (find_chr(tmp->content, '=') != 0)
			print_str(tmp->content);
		tmp = tmp->next;
	}
	get_info()->exit_status = 0;
	return (TRUE);
}

void	sort_env_arr(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (arr[i])
	{
		j = i - 1;
		tmp = arr[i];
		while (j >= 0 && ft_strcmp(arr[j], tmp) >= 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
		i++;
	}
}

void	unset_iter(t_list *pre_node, t_list *tmp_node)
{
	if (pre_node == NULL)
		get_info()->env_list = tmp_node->next;
	else
		pre_node->next = tmp_node->next;
	free(tmp_node->content);
	free(tmp_node);
}

int		unset(char *argv)
{
	t_list	*tmp_node;
	t_list	*pre_node;
	size_t	len;

	if (!is_identifier(argv[0]))
		return (print_error(PARSING_ERR, NULL));
	get_info()->exit_status = 0;
	len = ft_strlen(argv);
	pre_node = NULL;
	tmp_node = get_info()->env_list;
	while (tmp_node)
	{
		if ((!ft_strncmp(tmp_node->content, argv, len) &&
		((char *)tmp_node->content)[len] == '=') ||
		!ft_strncmp(tmp_node->content, argv, len + 1))
		{
			unset_iter(pre_node, tmp_node);
			return (TRUE);
		}
		pre_node = tmp_node;
		tmp_node = tmp_node->next;
	}
	return (TRUE);
}

int		unsets(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		unset(argv[i]);
		i++;
	}
	return (TRUE);
}
