#include "mini.h"

char	*concat_export_template(char *str)
{
	int		eq_index;
	char	*key_str;
	char	*value_str;
	char	*result;

	eq_index = find_chr(str, '=');
	if (eq_index == 0)
		return (ft_strjoin("declare -x ", str));
	else
	{
		value_str = ft_strdup("\"");
		value_str = free_join(value_str, ft_strdup(str + eq_index + 1));
		value_str = free_join(value_str, ft_strdup("\""));
		key_str = ft_substr(str, 0, eq_index + 1);
		key_str = free_join(key_str, value_str);
		result = ft_strjoin("declare -x ", key_str);
		free(key_str);
		return (result);
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

void	export_key(char *argv)
{
	t_list	*temp;
	size_t	size;

	temp = get_info()->env_list;
	size = ft_strlen(argv);
	while (temp)
	{
		if (!ft_strncmp(argv, temp->content, size))
		{
			if (((char *)temp->content)[size] == '\0' ||
			 ((char *)temp->content)[size] == '=')
				return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(&get_info()->env_list, ft_lstnew(ft_strdup(argv)));
}

int		export(char *argv)
{
	t_list	*temp;
	int		eq_index;

	temp = get_info()->env_list;
	eq_index = find_chr(argv, '=');
	if (!is_identifier(argv[0]))
		return (print_error(PARSING_ERR, NULL));
	if (eq_index != 0)
	{
		while (temp)
		{
			if (!ft_strncmp(argv, temp->content, eq_index))
			{
				free(temp->content);
				temp->content = ft_strdup(argv);
				return (TRUE);
			}
			temp = temp->next;
		}
		ft_lstadd_back(&get_info()->env_list, ft_lstnew(ft_strdup(argv)));
	}
	else
		export_key(argv);
	return (TRUE);
}

int		exports(char **argv)
{
	int		i;
	int		size;

	i = 1;
	size = len(argv);
	get_info()->exit_status = 0;
	if (size == 1)
		export_only();
	else if (size == 2)
		export(argv[1]);
	else
	{
		while (argv[i])
		{
			export(argv[i]);
			i++;
		}
	}
	return (TRUE);
}
