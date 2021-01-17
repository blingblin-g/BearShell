/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:34:16 by chlim             #+#    #+#             */
/*   Updated: 2021/01/17 21:00:06 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_env_item(char *key)
{
	int		i;
	int		eq_index;
	char	*arr[2];
	char	*value;
	t_list	*env_lst;

	i = 0;
	env_lst = get_info()->env_list;
	value = ft_strdup("");
	while (env_lst)
	{
		eq_index = find_chr(env_lst->content, '=');
		arr[0] = ft_substr(env_lst->content, 0, eq_index);
		arr[1] = ft_strdup(env_lst->content + eq_index + 1);
		if (!ft_strncmp(arr[0], key, ft_strlen(key) + 1))
		{
			free(value);
			value = ft_strdup(arr[1]);
		}
		free(arr[0]);
		free(arr[1]);
		env_lst = env_lst->next;
	}
	return (value);
}

t_list	*create_env_list(char **environ)
{
	t_list	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
	return (env_list);
}

char	**get_environ(void)
{
	t_list	*tmp_lst;
	char	**environ;
	size_t	size;
	size_t	i;

	size = ft_lstsize(get_info()->env_list);
	if (!(environ = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	environ[size] = 0;
	i = 0;
	tmp_lst = get_info()->env_list;
	while (tmp_lst)
	{
		environ[i] = tmp_lst->content;
		i++;
		tmp_lst = tmp_lst->next;
	}
	return (environ);
}

int		is_identifier(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (TRUE);
	return (FALSE);
}
