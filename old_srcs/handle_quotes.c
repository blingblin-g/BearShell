#include "mini.h"

/*
** comment
*/

/*
** check if it is valid to be used
*/

int is_valid_name(char c)
{
    if (ft_isalnum(c) || c == '_')
        return TRUE;
    return FALSE;
}

/*
** check if out of quotes is end
*/

int is_outofquote_end(char c)
{
    if (c == '\"' || c == '\'' || c == '\0')
        return (TRUE);
    return (FALSE);
}

/*
** check if it is escape sequence (after '\\')
*/

int is_escape(char c)
{
    if (c == '$' || c == '\"' || c == '\\' || c == '`')
        return (TRUE);
    return (FALSE);
}

/*
** check if it has sayeon which is complex process
*/

int is_sayeon(char c)
{
    if (c == '?' || c == '$' || c == '-' || ft_isdigit(c) || c == '!' || c == '@' || c == '*' || c == '#')
        return (TRUE);
    return (FALSE);
}

/*
** character after $ makes sayeon values.
** $? means exit status.
** $$ means PID
** $- means status of bash. it shows "himBH"
** $0 shows name of present shell.
** $# shows zero. don't know what it means.
** else doesn't show anything
*/

void process_sayeon(char c, char **result)
{
    if (c == '?')
        *result = free_join(*result, ft_itoa(get_info()->exit_status)); // 얘는 종료상태 이거 가져오는 애가 있거든요
    if (c == '$')
        *result = free_join(*result, ft_itoa(get_info()->pid)); // 얘는 PID
    if (c == '-')
        *result = free_join(*result, ft_strdup("himBH")); // himBH 이거요? 걍 write(1, "himBH", 5);
    if ((c > '0' && c <= '9') || c == '!' || c == '@' || c == '*')
        ;
    if (c == '0')
        *result = free_join(*result, ft_strdup("minishell"));
    if (c == '#')
        *result = free_join(*result, ft_strdup("0"));
}

/*
** find where is the end of the variable name, the range 
*/

char *find_var_name(char *content, size_t *i)
{
    size_t start;

    start = *i;
    while (is_valid_name(content[*i]))
        (*i)++;
    return (ft_substr(content, start, *i - start));
}

char *quotes_result(char *content, int *start, int *i, char *(*fp)(char *, size_t *, size_t *))
{
    char *result;
 	result = free_join(result, out_of_quotes_zone(content, start, i));
    result = free_join(result, fp(content, *start, *i));
    *start = ++(*i); // don't know this is ok... 넹
    return (result);
}

/*
** shorcut to the making result = free_join(old, new)
*/
char *new_result(char *content, int *start, int *i)
{
    char *result;

    result = free_join(result, ft_substr(content, *start, *i - *start));
    *start = ++(*i); // don't know this is ok...
    return (result);
}

/*
** initialize variables
*/

void init(t_parse *pars, char *result, int *i)
{
    *i = 0;
    pars->single_q = FALSE;
    pars->double_q = FALSE;
    pars->start = 0;
    result = ft_strdup("");
}

/*
** comment
*/

void is_qoutes_zone(t_parse *pars, char *content, size_t i)
{
    if (i == 0 || (i != 0 && content[i - 1] != '\\'))
    {
        if (content[i] == '\"')
            pars->double_q = TRUE;
        else if (content[i] == '\'')
            pars->single_q = TRUE;
    }
}

char *process_quotes(t_parse *pars, char *content)
{
    size_t i;
    size_t len;
    char *result;

    init(pars, result, &i);
    len = ft_strlen(content);
    while (i <= len)
    {
        if (!pars->single_q && !pars->double_q)
        {
            is_qoutes_zone(pars, content, i);
            if (!content[i])
                result = new_result(content, &pars->start, &i);
        }
        if (pars->single_q)
		{
			result = quotes_result(content, &pars->start, &i, out_of_quotes_zone);
			result = quotes_result(content, &pars->start, &i, get_single_quote_zone);
			pars->single_q = FALSE;
		}
		if (pars->double_q)
		{
			result = quotes_result(content, &pars->start, &i, out_of_quotes_zone);
			result = quotes_result(content, &pars->start, &i, get_double_quote_zone);
			pars->double_q = FALSE;
		}
		i++;
    }
}
