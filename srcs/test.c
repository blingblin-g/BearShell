#include "mini.h"

// static void	print_arr(char **arr) // input after pointer calc
// {
// 	while (*arr)
// 	{
// 		ft_putstr_fd(*arr, 1);
// 		if (arr + 1 != 0)
// 			write(1, " ", 1);
// 		arr++;
// 	}
// 	write(1, "\n", 1);
// }

int		main(void)
{
	// char *line = ft_strdup("$PWD     $: $ $/  'haha' you s'o    beautifu'l  $PWD");
	// char *text = "            e'ch'o haha' you' fool | echo m\"ero\"ng > result.txt ; cat result.txt | cat -e";
	// char *text = "echo '$chlim'$chlim\\|test | echo test";
	// char *text = "echo//test";
	// main_parse(line);
	// t_parse	pars;
	// printf("line: [%s]\n", line);
	// char *after_line = process_quotes(&pars, line);
	// printf("after process_quotes: [%s]\n", after_line);
	// char	**path = ft_split(get_env_item("PATH"), ':');

	// print_arr(path);
	// printf("cmd: [%s]\n", cmd);
	extern char **environ;
	char	*cmd = get_cmd("echo");
	char	**arr = ft_split("echo -n haha", ' ');

	printf("cmd: [%s]\n", cmd);
	if ((execve(cmd, arr, environ) == -1))
		printf("haha! you failed!\n");
	return (0);
}