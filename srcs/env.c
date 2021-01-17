/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:30:55 by chlim             #+#    #+#             */
/*   Updated: 2021/01/17 14:11:24 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		env(void)
{
	ft_lstiter(get_info()->env_list, print_str);
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

void	export_only(void)
{
	int		i;
	int		size;
	char	**env;
	t_list	*haha;

	size = ft_lstsize(get_info()->env_list);
	if (!(env = (char **)malloc(sizeof(char *) * (size + 1))))
		return ;
	env[size] = 0;
	haha = get_info()->env_list;
	i = 0;
	while (i < size)
	{
		env[i] = concat_export_template(haha->content);
		i++;
		haha = haha->next;
	}
	sort_env_arr(env);
	println_arr(env);
	free_arr(env);
}

int		export(char *argv)
{
	t_list	*temp;
	int		eq_index;

	temp = get_info()->env_list;
	eq_index = find_chr(argv, '=');
	if (eq_index != 0)
	{
		while (temp)
		{
			if (!ft_strncmp(argv, temp->content, eq_index + 1))
			{
				free(temp->content);
				temp->content = ft_strdup(argv);
				return (TRUE);
			}
			temp = temp->next;
		}
	}
	ft_lstadd_back(&get_info()->env_list, ft_lstnew(ft_strdup(argv)));
	return (TRUE);
}

int		unset(char *argv)
{
	t_list	*tmp_node;
	t_list	*pre_node;
	size_t	len;

	get_info()->exit_status = 0;
	len = ft_strlen(argv);
	pre_node = NULL;
	tmp_node = get_info()->env_list;
	while (tmp_node)
	{
		if (!ft_strncmp(tmp_node->content, argv, len) &&
		((char *)tmp_node->content)[len] == '=')
		{
			if (pre_node == NULL)
				get_info()->env_list = tmp_node->next;
			else
				pre_node->next = tmp_node->next;
			free(tmp_node->content);
			free(tmp_node);
			return (TRUE);
		}
		else if (!ft_strncmp(tmp_node->content, argv, len + 1))
		{
			if (pre_node == NULL)
				get_info()->env_list = tmp_node->next;
			else
				pre_node->next = tmp_node->next;
			free(tmp_node->content);
			free(tmp_node);
			return (TRUE);
		}
		
		pre_node = tmp_node;
		tmp_node = tmp_node->next;
	}
	return (TRUE);
}
