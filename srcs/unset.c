#include "mini.h"

void	unset(char *argv)
{
	t_list	*tmp_node;
	t_list	*pre_node;
	int		eq_index;

	tmp_node = get_info()->env_list;
	eq_index = find_chr(argv, '=');
	while (tmp_node)
	{
		if (!ft_strncmp(argv, tmp_node->content, eq_index))
		{
			if (tmp_node->next)
				pre_node->next = tmp_node->next;
			else
				pre_node->next = NULL;
			free(tmp_node->content);
			free(tmp_node);
			// free(argv);
			return ;
		}
		pre_node = tmp_node;
		tmp_node = tmp_node->next;
	}
}
