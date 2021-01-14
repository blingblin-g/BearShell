#include "mini.h"

void	process_sayeon(char c, char **result)
{
	if (c == '?')
		*result = free_join(*result, ft_itoa(get_info()->exit_status >> 8));
	if (c == '$')
		*result = free_join(*result, ft_itoa(get_info()->pid));
	if (c == '-')
		*result = free_join(*result, ft_strdup("himBH"));
	if ((c > '0' && c <= '9') || c == '!' || c == '@' || c == '*')
		;
	if (c == '0')
		*result = free_join(*result, ft_strdup("minishell"));
	if (c == '#')
		*result = free_join(*result, ft_strdup("0"));
}

char	*find_var_name(char *content, size_t *i)
{
	size_t start;

	start = *i;
	while (!how2divide(content[*i]))
		(*i)++;
	return (ft_substr(content, start, *i - start));
}

char	*process_home(char *content)
{
	char	*temp;
	char	*home_path;

	if ((content)[0] == '~')
	{
		if ((content)[1] == '/' || (content)[1] == '\0')
		{
			home_path = get_env_item("HOME");
			temp = ft_strjoin(home_path, (content) + 1);
			free(home_path);
			free(content);
			content = temp;
		}
	}
	return (content);
}