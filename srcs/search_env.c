#include <stdio.h>
#include "libft.h"

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
}

char	*get_env_item(char *key)
{
	extern char **environ;
	int		i;
	char	**arr;
	char	*value;

	i = 0;
	while (environ[i] != 0)
	{
		arr = ft_split(environ[i], '=');
		if (!ft_strncmp(arr[0], key, ft_strlen(key) + 1))
			value = ft_strdup(arr[1]);
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
	while (environ[i])
	{
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
	return (env_list);
}
