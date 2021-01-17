#include "mini.h"

char	*concat_export_template(char *str)
{
	int		eq_index;
	char	*key_str;
	char	*value_str;
	char	*result;

	eq_index = find_chr(str, '=');
	if (eq_index == 0)
		return (ft_strjoin("declare -x ", str));
	else
	{
		value_str = ft_strdup("\"");
		value_str = free_join(value_str, ft_strdup(str + eq_index + 1));
		value_str = free_join(value_str, ft_strdup("\""));
		key_str = ft_substr(str, 0, eq_index + 1);
		key_str = free_join(key_str, value_str);
		result = ft_strjoin("declare -x ", key_str);
		free(key_str);
		return (result);
	}
}

int		exports(char **argv)
{
	int		i;
	int		size;

	i = 1;
	size = len(argv);
	get_info()->exit_status = 0;
	if (size == 1)
		export_only();
	else if (size == 2)
		export(argv[1]);
	else
	{
		while (argv[i])
		{
			export(argv[i]);
			i++;
		}
	}
	return (TRUE);
}

int		unsets(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		fprintf(stderr, "argv[i]: [%s]\n", argv[i]);
		unset(argv[i]);
		i++;
	}
	return (TRUE);
}
