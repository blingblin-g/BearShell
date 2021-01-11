#include "mini.h"

int how2divide(char c)
{
	if (ft_isalnum(c) || c == '_')
		return FALSE;
	return TRUE;
}

int is_error(char c)
{
	if (c == '\'' || c == '\"' || c == '(' || c == ')' || c == '\\')
		return (TRUE);
	return (FALSE);
}

int is_outofquote_end(char c)
{
	if (c == '\"' || c == '\'' || c == '\0')
		return (TRUE);
	return (FALSE);
}

int is_escape(char c)
{
	if (c == '$' || c == '\"' || c == '\\' || c == '`')
		return (TRUE);
	return (FALSE);
}

int is_sayeon(char c)
{
	if (c == '?' || c == '$' || c == '-' || ft_isdigit(c) || c == '!' || c == '@' || c == '*' || c == '#')
		return (TRUE);
	return (FALSE);
}