#include "mini.h"

t_pro	*new_prolst(char *raw, int type)
{
	t_pro *new;

	new = (t_pro *)malloc(sizeof(t_pro));
	if (new == 0)
		return (0);
	new->raw = raw;
	new->type = type;
	new->cmd_lst = 0;
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

// only for test
void	print_prolst(t_pro *lst)
{
	while (lst)
	{
		printf("type == [%d] : raw == [%s]\n", lst->type, lst->raw);
		lst = lst->next;
	}
}
