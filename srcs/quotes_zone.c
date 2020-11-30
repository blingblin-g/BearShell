#include "mini.h"

int		how2divide(char c)
{
	if (ft_isalnum(c) || c == '_')
		return FALSE;
	return TRUE;
}

int		is_error(char c) // $ 다음 캐릭터를 넘겨줘요
{
	// 1. 에러인지 확인만 하는 거니까 통째로 해도 될 것 같거든요 지금 통자메이카 치킨 먹고 싶다
	if (c == '\'' || c == '\"' || c == '(' || c == ')' || c == '\\')
		return (TRUE);
	return (FALSE);
}

	// 2. 사연이 있는지
int		is_sayeon(char c, char **result)
{//여기서 덥해서 value찾아와서 프리조인해서 붙여넣기
	if (c == '?')
		;// 얘는 종료상태
	if (c == '$')
		;// 얘는 PID
	if (c == '-')
		;// himBH
	return (0);
} // echo test1 test2 test3
 // test $_
	// 3. is_alnum을 제외한 변수인지


char	*process_quotes(t_parse *pars, char *content)
{
	size_t	i;
	char	*result;
	// char	*tmp;

	i = 0;
	pars->single_q = FALSE;
	pars->double_q = FALSE;
	pars->start = 0;
	result = ft_strdup("");
	while (i <= ft_strlen(content))
	{
		if (!pars->single_q && !pars->double_q)
		{
			if ((how2divide(content[i])))
			{
				if (i < ft_strlen(content) - 1 && content[i] == '\\' && content[i + 1] == '\\')
					i++;
				else if (content[i] == '$')
				{			
					i++;							// $`!@#$?'"-_ 사연이 많은 애들
					// if (i < ft_strlen(content) - 1 && (tmp = builtin_dollor(content[i])))
					// 	result = free_join(result, tmp);
					if (ft_isalnum(content[i]))
					{
						pars->start = i;
						while (!how2divide(content[i]))
							i++;
						char *key = ft_substr(content, pars->start, i - pars->start);
						result = free_join(result, get_env_item(key));
						free(key);
						pars->start = i;
					}
					else
					{
						result = free_join(result, ft_substr(content, pars->start, i - pars->start));
						pars->start = i;
					}
					continue ;
				}
				result = free_join(result, ft_substr(content, pars->start, i - pars->start));
				if (!content[i])
					break ;
				pars->start = i;
			}
			if (i == 0 || (i != 0 && content[i - 1] != '\\'))
			{
				if (content[i] == '\"')
				{
					pars->double_q = TRUE;
					pars->start = i;
				}
				else if (content[i] == '\'')
				{
					pars->single_q = TRUE;
					pars->start = i;
				}
			}
		}
		if (pars->single_q)
		{
			// ''빼고 그대로 출력해준다;
			char	*sub_tmp = get_single_quote_zone(content, &i);
			printf("sub_tmp: [%s]\n", sub_tmp);
			pars->single_q = FALSE;
			pars->start = i;
		}
		if (pars->double_q)
		{
			// outofq에서 해준 과정을 통해서 가공해준다;
		}
		i++;
	}
	return (result);
}

size_t	search_pair_quotes(char c, char *line, size_t i) // return index of pair_quotes
{
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (ERROR); // 다 돌았지만 못찾은거임. 즉 pair quote가 없는 것
}

char	*get_single_quote_zone(char *content, size_t *i)
{
	size_t	size;
	char	*result;

	if ((size = search_pair_quotes('\'', content, *i)) == ERROR)
		return (0);
	result = ft_substr(content, *i, size - *i);
	// result = free_join(content, str);
	*i = (size + 1);
	return (result);
}
