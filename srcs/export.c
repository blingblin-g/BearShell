#include "mini.h"

void	export(char *argv)
{
	t_list	*temp;
	int		eq_index;

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