#include "mini.h"

int		how2divide(char c)
{
	if (ft_isalnum(c) || c == '_')
		return FALSE;
	return TRUE;
}

int		is_error(char c) // $ 다음 캐릭터를 넘겨줘요
{
	// 1. 에러인지 확인ㅇㅋㅇㅋ
	if (c == '\'' || c == '\"' || c == '(' || c == ')' || c == '\\')
		return (TRUE);
	return (FALSE);
}

char	*process_quotes(t_parse *pars, char *content)
{
	size_t	i;
	char	*result;

	i = 0;
	pars->single_q = FALSE;
	pars->double_q = FALSE;
	pars->start = 0;
	result = ft_strdup("");
	while (i <= ft_strlen(content))
	{
		if (!pars->single_q && !pars->double_q)
		{
			if (i == 0 || (i != 0 && content[i - 1] != '\\'))
			{
				if (content[i] == '\"')
				{
					pars->double_q = TRUE;
				}
				else if (content[i] == '\'')
				{
					pars->single_q = TRUE;
				}
			}
			if (!content[i])
			{
				result = free_join(result, ft_substr(content, pars->start, i - pars->start));
			}
		}
		if (pars->single_q)
		{
			result = free_join(result, ft_substr(content, pars->start, i - pars->start));
			pars->start = i;
			result = free_join(result, get_single_quote_zone(content, &i));
			pars->single_q = FALSE;
			pars->start = i;
		}
		if (pars->double_q)
		{
			result = free_join(result, ft_substr(content, pars->start, i - pars->start));
			pars->start = i;
			result = free_join(result, get_double_quote_zone(content, &i));
			pars->double_q = FALSE;
			pars->start = i;
		}
		i++;
	}
	return (result);
}

size_t	search_pair_singleq(char *line, size_t i) // return index of pair_quotes
{
	while (line[i])
	{
		if (line[i] == '\'')
			return (i);
		i++;
	}
	return (ERROR); // 다 돌았지만 못찾은거임. 즉 pair quote가 없는 것
}

char	*get_single_quote_zone(char *content, size_t *i)
{
	size_t	size;
	char	*result;

	(*i)++;
	if ((size = search_pair_singleq(content, *i)) == ERROR)
		return (0);
	result = ft_substr(content, *i, size - *i);
	*i = (size + 1);
	return (result);
}

int		is_escape(char c)
{
	if (c == '$' || c == '\"' || c == '\\' || c == '`')
		return (TRUE);
	return (FALSE);
}

int		is_sayeon(char c)
{
	if (c == '?' || c == '$' || c == '-' || ft_isdigit(c) || c == '!' || c == '@' || c == '*' || c == '#')
		return (TRUE);
	return (FALSE);
}
 
void		process_sayeon(char c, char **result)
{//여기서 덥해서 value찾아와서 프리조인해서 붙여넣기
	if (c == '?')
		*result = free_join(*result, ft_itoa(get_info()->exit_status));// 얘는 종료상태 이거 가져오는 애가 있거든요 
	if (c == '$')
		*result = free_join(*result, ft_itoa(get_info()->pid));// 얘는 PID
	if (c == '-')
		*result = free_join(*result, ft_strdup("himBH"));// himBH 이거요? 걍 write(1, "himBH", 5);
	if ((c > '0' && c <= '9') || c == '!' || c == '@' || c == '*')
		;
	if (c == '0')
		*result = free_join(*result, ft_strdup("minishell"));
	if (c == '#')
		*result = free_join(*result, ft_strdup("0"));
}

char	*find_var_name(char *content, size_t *i)
{
	size_t	start;

	start = *i;
	while (!how2divide(content[*i]))
		(*i)++;
	return (ft_substr(content, start, *i - start));
}

size_t	search_pair_doubleq(char *line, size_t i) // return index of pair_quotes
{
	while (line[i])
	{
		if (line[i] == '\"')
			return (i);
		i++;
	}
	return (ERROR); // 다 돌았지만 못찾은거임. 즉 pair quote가 없는 것
}

char	*get_double_quote_zone(char *content, size_t *i)
{
	size_t	start;
	char	*result;
	char	*var_name;

	(*i)++;
	start = *i;
	result = ft_strdup("");
	while (*i <= ft_strlen(content))
	{
		if (!content[*i]) // double q가 닫히지 않았는데 null이 나왔으므로 에러 처리
			return (NULL);
		if (content[*i] == '\\')
		{
			result = free_join(result, ft_substr(content, start, *i - start));
			start = *i;
			if (is_escape(content[*i + 1]))
				start = ++(*i);
		}
		else if (content[*i] == '$')
		{
			result = free_join(result, ft_substr(content, start, *i - start));
			start = ++(*i);
			if (is_sayeon(content[*i]))
			{
				process_sayeon(content[*i], &result);
				start = *i + 1;
			}
			else if (how2divide(content[*i]))
			{
				result = free_join(result, ft_strdup("$"));
				(*i)--;
			}
			else
			{
				var_name = find_var_name(content, i);
				result = free_join(result, get_env_item(var_name));
				free(var_name);
				start = (*i)--;
			}
		}
		else if (content[*i] == '\"')
		{
			result = free_join(result, ft_substr(content, start, *i - start));
			(*i)++;
			break;
		}
		(*i)++;
	}
	return (result);
}
