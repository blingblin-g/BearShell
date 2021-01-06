#include "mini.h"

char	*get_env_item(char *key)
{
	extern char **environ;
	int		i;
	char	**arr;
	char	*value;

	i = 0;
	value = ft_strdup("");
	while (environ[i] != 0)
	{
		arr = ft_split(environ[i], '=');
		if (!ft_strncmp(arr[0], key, ft_strlen(key) + 1))
		{
			free(value);
			value = ft_strdup(arr[1]);
		}
		free_arr(arr);
		i++;
	}
	return (value);
}

t_list	*create_env_list()
{
	extern char **environ;
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

char	**get_environ()
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
