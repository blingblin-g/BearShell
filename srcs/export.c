#include "mini.h"




void		print_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], 1);
		arr[i] = 0;
		i++;
	}
}

char	**sort_env(char **env)
{
	// sooyoon is going to implement by selection sort
}

char	**export_only()
{
	int		i;
	int		size;
	char	**env;
	t_list	*haha;

	size = ft_lstsize(get_info()->env_list);
	if (!(env = (char **)malloc(sizeof(char *) * (size + 1))))
		return 0;
	env[size] = 0;
	haha = get_info()->env_list;
	i = 0;
	while (i < size)
	{
		env[i] = ft_strjoin("declare -x", haha->content);
		i++;
		haha = haha->next;
	}
	return (env);
}

void	export(char *argv)
{
	t_list	*temp;
	int		eq_index;

	if (!argv)
		return (export_only());
	temp = get_info()->env_list;
	eq_index = find_chr(argv, '=');
	while (temp)
	{
		if (!ft_strncmp(argv, temp->content, eq_index))
		{
			free(temp->content);
			temp->content = argv;
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&get_info()->env_list, ft_lstnew(argv));
}