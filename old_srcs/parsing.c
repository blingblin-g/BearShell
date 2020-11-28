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

int		is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '\0' || c == ' ')
		return (TRUE);
	return FALSE;
}

int		search_command_end(char *line, int i)
{
	while (line[i])
	{
		if (is_special_char(line[i]))
			return (i);
		i++;
	}
	return (ERROR);
}

void	is_out_of_quote_zone(t_parse *pars, int *i, char **content)
{
	int		cmd_end = search_command_end(pars->line, *i);
	char	*str;
	t_cmd	*cmd;

	cmd = NULL;
	printf("cmd_end: [%d]\n", cmd_end);
	if (pars->line[cmd_end] == ' ')
	{
		str = ft_substr(pars->line, *i, cmd_end - *i);
		printf("content: [%p]\n", content);
		*content = free_join(*content, str);
		pars->is_space = TRUE;
	}
	if (pars->line[cmd_end] == '|')
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->type = PIPE;
	}
	if (pars->line[cmd_end] == '>')
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (pars->line[cmd_end + 1] == '>')
		{
			cmd->type = APPEND;
			(*i)++;
		}
		else
			cmd->type = OUTPUT;
	}
	if (pars->line[cmd_end] == '<')
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->type = INPUT;
	}
	if (cmd)
		ft_lstadd_back(&pars->pro_lst, ft_lstnew(cmd));
	*i = cmd_end + 1;
}

char	**last_content(t_parse *pars)
{
	t_list	*last_pro_list;
	t_cmd	*tmp_cmd;

	last_pro_list = ft_lstlast(pars->pro_lst);
	tmp_cmd = last_pro_list->content;
	printf("tmp_cmd: [%p]\n", tmp_cmd);
	printf("tmp_cmd->cmd_lst: [%p]\n", tmp_cmd->cmd_lst);
	return (ft_lstlast(tmp_cmd->cmd_lst)->content);
}

int	main_parse(char *line)
{
	t_parse	pars;
	int		i;
	int		is_space;

	i = 0;
	is_space = TRUE;
	pars.line = line;
	pars.pro_lst = ft_lstnew(malloc(sizeof(t_cmd)));
	t_list	*tmp_lst = ft_lstnew(ft_strdup(""));
	((t_cmd *)pars.pro_lst->content)->cmd_lst = tmp_lst;
	printf("pars.pro_lst->content: [%p]\n", pars.pro_lst->content);
	while (line[i])
	{
		printf("i: [%d]\n", i);
		// if (is_space == 0 && line[i] == ' ')
		// {
		// 	is_space = 1;
		// 	ft_lstadd_back(&pars.cmd_lst, ft_lstnew(ft_strdup("")));
		// }
		// else if (!pars.single_q && !pars.double_q && line[i] == ' ')
		// 	continue;
		// else if (line[i] != ' ')
		// 	is_space = 0;

		// if (line[i] == '\'')
		// 	pars.single_q = TRUE;
		if (/*pars.single_q */line[i] == '\'')
		{
			++i;
			if (is_single_quote_zone(&pars, &i, last_content(&pars)) == ERROR)
				return (ERROR);
			pars.single_q = FALSE;
		}
		// is_double_quote_zone();
		// if (line[i] != '\'' || line[i] != '\"')
		is_out_of_quote_zone(&pars, &i, last_content(&pars)); // 공백을 만나면 new cmd list
		i++;
	}

	for (t_list *tmp = ((t_cmd *)(pars.pro_lst->content))->cmd_lst; tmp != NULL; tmp = tmp->next)
	{
		printf("tmp: [%s]\n", (char *)tmp->content);
	}
	return (TRUE);
}