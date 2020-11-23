#include "mini.h"

int		main(void)
{
    // char	*inputs1[30] = {"echo123123", "test write"};
	// char	*inputs2[30] = {"echo11111111111", "-n", "test write"};

    // echo(inputs1);
	// printf("\n======================\n");
	// echo(inputs2);

	// char	buf[2097152];
	// char	*result;

	// result = getcwd(buf, 2097152);
	// printf("%s   : result=>[%s]\n", buf, result);

	// ft_lstiter(list, print_str);

	get_info()->env_list = create_env_list();
	// char *str = ft_strdup("HOME=/Users/sooyoon");
	// char *str2 = ft_strdup("chlim=sooyoon");
	// // export(str);
	// export(str2);
	// env();
	// printf("\n======================\n");
	// unset(str);
	// ft_lstiter(get_info()->env_list, print_str);
	// free(str);
	// free(str2);
	export(NULL);
    return (0);
}