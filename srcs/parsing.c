#include "mini.h"

char	*free_join(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;
	char *result;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(result = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return(0);
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		result[len1 + i] = s2[i];
		i++;
	}
	result[len1 + len2] = 0;
	free(s1);
	free(s2);
	return (result);
}


int		search_pair_quotes(char c, char *line, int i) // return index of pair_quotes
{
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (ERROR); // 다 돌았지만 못찾은거임. 즉 pair quote가 없는 것
}

int		is_double_quote_zone();
#include <stdio.h>
int		is_single_quote_zone(t_parse *pars, int *i, char **content)
{
	// e'ch'o 'h'a'ha' 'ha'
	// 기존 리스트에 이어붙일지, 새로 추가할지
	int	size;
	char *str;
	// char *tmp;

	if ((size = search_pair_quotes('\'', pars->line, *i)) == ERROR)
		return (ERROR);
	// printf("size == [%d], i == [%d]\n", size, *i);
	str = ft_substr(pars->line, *i, size - *i);
	// printf("str == [%s]\n", str);
	*content = free_join(*content, str);
	*i = (size + 1);
	return (SUCCESS);
}

int		is_out_of_quote_zone();

void	main_parse(char *line)
{
	int		i;
	t_parse pars;
	int		is_space;

	i = 0;
	is_space = 1;
	pars.line = line;
	pars.cmd_lst = ft_lstnew(ft_strdup(""));
	while (line[i])
	{
		// if (is_space == 0 && line[i] == ' ')
		// {
		// 	is_space = 1;
		// 	ft_lstadd_back(&pars.cmd_lst, ft_lstnew(ft_strdup("")));
		// }
		// else if (!pars.single_q && !pars.double_q && line[i] == ' ')
		// 	continue;
		// else if (line[i] != ' ')
		// 	is_space = 0;

		if (line[i] == '\'')
			pars.single_q = TRUE;
		if (pars.single_q)
		{
			++i;
			is_single_quote_zone(&pars, &i, (char **)&(ft_lstlast(pars.cmd_lst)->content));
		}
		// is_double_quote_zone();
		
		// is_out_of_quote_zone(); // 공백을 만나면 new cmd list
		i++;
	}

	for (t_list *tmp = pars.cmd_lst; tmp != NULL; tmp = tmp->next)
	{
		printf("tmp: [%s]\n", (char *)tmp->content);
	}
}