#include "mini.h"

int		main(void)
{
    // char	*inputs1[30] = {"echo123123", "test write"};
	// char	*inputs2[30] = {"echo11111111111", "-n", "test write"};

    // echo(inputs1);
	// printf("\n======================\n");
	// echo(inputs2);

	char	buf[2097152];
	char	*result;

	result = getcwd(buf, 2097152);
	printf("%s   : result=>[%s]\n", buf, result);
    return (0);
}