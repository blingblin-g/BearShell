#include "mini.h"

int		how2divide(char c)
{
	if (ft_isalnum(c) || c == '_')
		return FALSE;
	return TRUE;
}

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
					}
					i++;
					continue ;
				}
				result = free_join(result, ft_substr(content, pars->start, i - pars->start));
				if (!content[i])
					break ;
				pars->start = i + 1;
			}
			// if (content[i] == '$') // $변수에 대한 처리를 해준다. $'"\를 만날때까지
			// {
			// 	i++;
			// 	if (content[i] != '\'' && content[i] != '\"')
					// 본인은 사라져버림..
			// 		// env에 있는 (변수) key값으로 넣어서 value값으로 치환;
			// 		// 없으면 그냥 "\n"
			// 	else if (content[i] == '<' , '[' '(' 등등 안되는 것들이면)
			// 	{
			// 		// error를 띄운다;
			// 	}
			// 	else if (content[i] == '?')
			// 		// 종료상태 저장했던 값을 넣어준다;
			// 	else if (content[i] == '$')
			// 		// PID값 출력
			// 	else if (content[i] == 'P' ~ PPID)
			// 		// PPID값 출력
			// 	else
			// 	{
			// 		// 그대로 쓴다;
			// 		// 단, if (quote가 또...)
			// 			// quote를 빼고 가공해서 넣어준다;
			// 	}
			// }
			// if (i == 0 || (i != 0 && content[i - 1] != '\\'))
			// {
			// 	if (content[i] == '\"')
			// 	{
			// 		pars->double_q = TRUE;
			// 		pars->start = i;
			// 	}
			// 	else if (content[i] == '\'')
			// 	{
			// 		pars->single_q = TRUE;
			// 		pars->start = i;
			// 	}
			// }
		}
		if (pars->single_q)
		{
			// ''빼고 그대로 출력해준다;

		}
		if (pars->double_q)
		{
			// outofq에서 해준 과정을 통해서 가공해준다;
		}
		i++;
	}
	return (result);
}