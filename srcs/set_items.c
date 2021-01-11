#include "mini.h"

int		set_string(char **old_str, char *new_str)
{
	if (*old_str != NULL)
		free(*old_str);
	*old_str = ft_strdup(new_str);
	if (old_str == NULL)
		return (FALSE);
	return (TRUE);
}

int		set_process_name(char *name)
{
	if (!ft_strcmp(NAME, name))
		get_info()->process_index = 0;
	else
		get_info()->process_index++;
	return (set_string(&(get_info()->process_name), name));
}