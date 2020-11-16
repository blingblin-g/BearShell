#include "mini.h"

void	print_str(void *str)
{
	printf("[%s]\n", (char *)str);
}

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
	export("chlim", "rockpell");
    return (0);
}