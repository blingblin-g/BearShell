#include "mini.h"

static void	print_arr(char **arr)
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

void	sort_env_arr(char **arr)
{
    int i = 0;
    int j = 0;
    char *tmp = 0;

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

void	export_only()
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
		env[i] = ft_strjoin("declare -x ", haha->content);
		i++;
		haha = haha->next;
	}
	sort_env_arr(env);
	print_arr(env);
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