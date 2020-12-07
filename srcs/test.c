#include "mini.h"

// static void	print_arr(char **arr) // input after pointer calc
// {
// 	while (*arr)
// 	{
// 		ft_putendl_fd(*arr, 1);
// 		// if (arr + 1 != 0)
// 		// 	write(1, " ", 1);
// 		arr++;
// 	}
// }

int		main(void)
{
	// char *line = ft_strdup("$PWD     $: $ $/  'haha' you s'o    beautifu'l  $PWD");
	// char *line = ft_strdup("            e'ch'o haha' you' fool | echo m\"ero\"ng > result.txt ; cat result.txt | cat -e");
	// char *line = ft_strdup("dobule \'\"\'sq_in_dq\"\'\"dq_in_sq\"\\abc\\haha\\\\sooyoon$chlim$chlim$1haha $\\ $; $+ $?\"earlose tear\"$chlim\"lose");
	// char *line = ft_strdup("\"$\"");
	// char *line = ft_strdup("hahah\\you$chlim  \"test $chlim \"");

	// char *text = "echo '$chlim'$chlim\\|test | echo test";
	// char *text = "echo//test";
	// main_parse(line);
	
	// t_parse	pars;
	// printf("line: [%s]\n", line);
	// char *after_line = process_quotes(&pars, line);
	// printf("after process_quotes: [%s]\n", after_line);

	// char	**path = ft_split(get_env_item("PATH"), ':');

	// print_arr(path);

	// extern char **environ;
	// char	*cmd = get_cmd("echo");
	// char	**arr = ft_split("echo -n haha", ' ');

	// printf("cmd: [%s]\n", cmd);
	// if ((execve(cmd, arr, environ) == -1))
	// 	printf("haha! you failed!\n");
	// char	*text = ft_strdup("aaaa\\n");
	
	// size_t		i = 0;

	// char	*result = get_double_quote_zone(line, &i);
	// printf("[%s]\n", result);

	// char *result = out_of_quotes_zone(line, &i);
	// printf("[%s]\n", result);



	printf("=================mild==============\n");
	
	char **tests = malloc(sizeof(char *) * 30);
	tests[0] = ft_strdup("\'$USER\'");
	tests[1] = ft_strdup("\"$USER\"");
	tests[2] = ft_strdup("\"\'$USER\'\"");
	tests[3] = ft_strdup("\'\"$USER\"\'");
	tests[4] = ft_strdup("\'\'$USER\'\'");
	tests[5] = ft_strdup("\'\'\'$USER\'\'\'");
	tests[6] = ft_strdup("$USER=aaa");
	tests[7] = ft_strdup("$HELLO=aaa");

	for (int i = 0; i < 8; i++)
	{
		t_parse	pars;
		char *after_line = process_quotes(&pars, tests[i]);
		printf("[%d]============================[%s]\n", i, after_line);
	}

	printf("=================bit of spicy==============\n");

	tests[8] = ft_strdup("aa\"bb$USER\"cc");
	tests[9] = ft_strdup("aa\"bb$USER cc\"dd");
	tests[10] = ft_strdup("aa\"bb$USERcc\"dd");
	tests[11] = ft_strdup("\'qqq\\\'");
	tests[12] = ft_strdup("hello$USER_");
	tests[13] = ft_strdup("\"hello\\nman\"");
	tests[14] = ft_strdup("hello\\nman");
	tests[15] = ft_strdup("\"hello\\ man\"");
	tests[16] = ft_strdup("\"hello\'man\"");
	tests[17] = ft_strdup("\"hello\'man\\\"\"");
	tests[18] = ft_strdup("\'hello\"man\'");

	for (int i = 8; i < 19; i++)
	{
		t_parse	pars;
		char *after_line = process_quotes(&pars, tests[i]);
		printf("[%d]============================[%s]\n", i, after_line);
	}

	printf("=================lot of spicy==============\n");
	
	tests[19] = ft_strdup("ec\"\"\"ho\"\"\" hello");
	tests[20] = ft_strdup("ec\"ho\" hello");
	tests[21] = ft_strdup("ec\'ho\' hello");
	tests[22] = ft_strdup("ec\"\'ho\'\" hello");
	tests[23] = 0;

	for (int i = 19; i < 23; i++)
	{
		t_parse	pars;
		char *after_line = process_quotes(&pars, tests[i]);
		printf("[%d]============================[%s]\n", i, after_line);
	}

	// t_parse	pars;
	// char *line = ft_strdup("\'\'\'$USER\'\'\'");
	// char *after_line = process_quotes(&pars, line);
	// printf("line: [%s]\n", line);
	// printf("[%s]\n", after_line);
	return (0);
}