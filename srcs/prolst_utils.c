#include "mini.h"

t_pro	*new_prolst(char *raw, int type)
{
	t_pro *new;

	new = (t_pro *)malloc(sizeof(t_pro));
	if (new == 0)
		return (0);
	new->raw = raw;
	new->type = type;
	new->pipe_lst = NULL;
	new->cmd_lst = NULL;
	new->next = 0;
	return (new);
}

t_pro	*last_prolst(t_pro *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back_prolst(t_pro **lst, t_pro *new)
{
	t_pro *last;

	if (*lst == 0)
		*lst = new;
	last = last_prolst(*lst);
	last->next = new;
	new->next = 0;
}
/*
* do not need to free prolst outside
*/
void	free_prolst(t_pro **lst)
{
	t_pro	*next_lst;

	while (*lst)
	{
		next_lst = (*lst)->next;
		free((*lst)->raw);
		ft_lstclear(&(*lst)->cmd_lst, free);
		ft_lstclear(&(*lst)->pipe_lst, free);
		free((*lst)->cmd_lst);
		free((*lst)->pipe_lst);
		free(*lst);
		*lst = next_lst;
	}
}

char	*free_strtrim(char **s, char const *set)
{
	char	*result;

	result = ft_strtrim(*s, set);
	free(*s);
	return (result);
}
