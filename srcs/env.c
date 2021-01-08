#include "mini.h"

int env()
{
	ft_lstiter(get_info()->env_list, print_str);
	return (TRUE);
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
	println_arr(env);
}

int		export(char *argv)
{
	t_list	*temp;
	int		eq_index;

	if (!argv)
	{
		export_only();
		return TRUE;
	}
	temp = get_info()->env_list;
	eq_index = find_chr(argv, '=');
	while (temp)
	{
		if (!ft_strncmp(argv, temp->content, eq_index))
		{
			free(temp->content);
			temp->content = argv;
			return (TRUE);
		}
		temp = temp->next;
	}
	ft_lstadd_back(&get_info()->env_list, ft_lstnew(argv));
	return (TRUE);
}

int		unset(char *argv)
{
	t_list	*tmp_node;
	t_list	*pre_node;
	size_t len;
	
	len = ft_strlen(argv);
	pre_node = NULL;
	tmp_node = get_info()->env_list;
	while (tmp_node)
	{
		if (!ft_strncmp(tmp_node->content, argv, len &&
		 ((char *)tmp_node->content)[len] == '='))
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