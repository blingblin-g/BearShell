#include "mini.h"

void	fill_result(char **result, char *content, size_t *start, size_t *i)
{
	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = *i;
}

void	fill_result_plus_start(char **result, char *content, size_t *start, size_t *i)
{
	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = *i + 1;
}

void	fill_result_plus_i(char **result, char *content, size_t *start, size_t *i)
{
	*result = free_join(*result, ft_substr(content, *start, *i - *start));
	*start = ++(*i);
}
