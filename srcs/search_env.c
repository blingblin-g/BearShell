#include <stdio.h>
#include "libft.h"

extern char **environ;

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

char	*get_env_item(char *item)
{
	int		i;
	char	**arr;
	char	*result;

	i = 0;
	while (environ[i] != 0)
	{
		arr = ft_split(environ[i], '=');
		if (!ft_strncmp(arr[0], item, ft_strlen(item) + 1))
			result = ft_strdup(arr[1]);
		free_arr(arr);
		i++;
	}
	return (result);
}
