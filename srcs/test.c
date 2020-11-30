#include "mini.h"

int		main(void)
{
	char *line = ft_strdup("$PWD     $: $ $/  'haha' you s'o    beautifu'l  $PWD");
	// char *text = "            e'ch'o haha' you' fool | echo m\"ero\"ng > result.txt ; cat result.txt | cat -e";
	// char *text = "echo '$chlim'$chlim\\|test | echo test";
	// char *text = "echo//test";
	// main_parse(line);
	t_parse	pars;
	printf("line: [%s]\n", line);
	char *after_line = process_quotes(&pars, line);
	printf("after process_quotes: [%s]\n", after_line);
	return (0);
}