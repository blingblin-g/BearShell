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

int prolst_size(t_pro *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return count;
}

int		cmdlst_size(t_list *lst)
{
	int count;

	count = 0;
	while (lst)
	{
		if (((char *)lst->content)[0]) // 배열인덱스가 나을지 포인터가 나을지 선택 바람.
			count++;
		lst = lst->next;
	}
	return (count);
}

void	print_exec_info(t_exec *exec_info)
{
	int	i = 0;

	while (i < exec_info->argv_idx)
	{
		printf("argv[%d]: [%s]\n", i, exec_info->argv[i]);
		i++;
	}
	i = 0;
	while (i < exec_info->fd_input_idx)
	{
		printf("input_idx[%d]: [%d]\n", i, exec_info->fd[0][i]);
		i++;
	}
	i = 0;
	while (i < exec_info->fd_output_idx)
	{
		printf("output_idx[%d]: [%d]\n", i, exec_info->fd[1][i]);
		i++;
	}
}

// only for test
void	print_prolst(t_pro *lst)
{
	t_parse	pars;
	t_list	*pipe_lst;
	t_list	*redirection_lst;
	t_exec	*exec_info;

	init_pars(&pars);
	while (lst)
	{
		printf("type == [%d] : raw == [%s]\n", lst->type, lst->raw);
		pipe_lst = lst->pipe_lst;
		while (pipe_lst)
		{
			redirection_lst = NULL;
			printf("pipe_lst == [%s]\n", (char *)pipe_lst->content);
			if (input_redirection_lst(&pars, pipe_lst->content, &redirection_lst))
			{
				exec_info = create_exec(&pars, redirection_lst);
				print_exec_info(exec_info);
			}
			pipe_lst = pipe_lst->next;
		}
		lst = lst->next;
	}
}

int main(void)
{
	t_parse pars;
	// char *line = ft_strdup("$PWD     $: $ $/  'haha' you s'o    beautifu'l  $PWD");
	// char *line = ft_strdup("            e'ch'o haha' you' fool | echo m\"ero\"ng > result.txt ; cat result.txt | cat -e");
	// char *line = ft_strdup("dobule \'\"\'sq_in_dq\"\'\"dq_in_sq\"\\abc\\haha\\\\sooyoon$chlim$chlim$1haha $\\ $; $+ $?\"earlose tear\"$chlim\"lose");
	// char *line = ft_strdup("\"$\"");
	char *line = ft_strdup("echo '$chlim' $chlim \\|test ;>$chlim echo test >> echo redirection<echo input > echo output >\\>\\<\\>>\\>>");
	// char *line = ft_strdup("echo test | cat");
	// char *line = ft_strdup("echo test| echo test> sample ; cat | cat | cat");
	// char *line = ft_strdup("echo haha > mkdir yoyo abc > mkdir2 hehe haha");
	// char *line = ft_strdup("echo haha yoyo abc hehe haha > mkdir > mkdir2");
	// char *line = ft_strdup("echo haha > echo test1 '>'test2>test3;echo test>temp.txt");
	// int cmd_size;
	int pro_size;
	// t_parse pars; 이게 지금 지역변수로 선언돼있어서
	// 먼저 세미콜론으로 파싱 => 세미리스트(지금은 pro_lst로 되있음) => | 파싱 => 파이프리스트
	// => 파이프 리스트 안에 있는 리디렉션 처리 => 파이프 리스트는 실행시에 동시 실행되야함
	// => 세미리스트는 그냥 순차적으로 실행

	init_pars(&pars);
	// pars.pro_lst->next = NULL;
	printf("line: [%s]\n", line);
	main_parse(line, &pars);
	print_prolst(pars.pro_lst); // only 4 test
	pro_size = prolst_size(pars.pro_lst);
	printf("pro_size: [%d]\n", pro_size);
	// cmd_size = cmdlst_size();

	// print_prolst(pars.pro_lst);
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

	// printf("=================mild==============\n");

	// char **tests = malloc(sizeof(char *) * 30);
	// tests[0] = ft_strdup("\'$USER\'");
	// tests[1] = ft_strdup("\"$USER\"");
	// tests[2] = ft_strdup("\"\'$USER\'\"");
	// tests[3] = ft_strdup("\'\"$USER\"\'");
	// tests[4] = ft_strdup("\'\'$USER\'\'");
	// tests[5] = ft_strdup("\'\'\'$USER\'\'\'");
	// tests[6] = ft_strdup("$USER=aaa");
	// tests[7] = ft_strdup("$HELLO=aaa");

	// for (int i = 0; i < 8; i++)
	// {
	// 	t_parse	pars;
	// 	char *after_line = process_quotes(&pars, tests[i]);
	// 	printf("[%d]============================[%s]\n", i, after_line);
	// }

	// printf("=================bit of spicy==============\n");

	// tests[8] = ft_strdup("aa\"bb$USER\"cc");
	// tests[9] = ft_strdup("aa\"bb$USER cc\"dd");
	// tests[10] = ft_strdup("aa\"bb$USERcc\"dd");
	// tests[11] = ft_strdup("\'qqq\\\'");
	// tests[12] = ft_strdup("hello$USER_");
	// tests[13] = ft_strdup("\"hello\\nman\"");
	// tests[14] = ft_strdup("hello\\nman");
	// tests[15] = ft_strdup("\"hello\\ man\"");
	// tests[16] = ft_strdup("\"hello\'man\"");
	// tests[17] = ft_strdup("\"hello\'man\\\"\"");
	// tests[18] = ft_strdup("\'hello\"man\'");

	// for (int i = 8; i < 19; i++)
	// {
	// 	t_parse	pars;
	// 	char *after_line = process_quotes(&pars, tests[i]);
	// 	printf("[%d]============================[%s]\n", i, after_line);
	// }

	// printf("=================lot of spicy==============\n");

	// tests[19] = ft_strdup("ec\"\"\"ho\"\"\" hello");
	// tests[20] = ft_strdup("ec\"ho\" hello");
	// tests[21] = ft_strdup("ec\'ho\' hello");
	// tests[22] = ft_strdup("ec\"\'ho\'\" hello");
	// tests[23] = 0;

	// for (int i = 19; i < 23; i++)
	// {
	// 	t_parse	pars;
	// 	char *after_line = process_quotes(&pars, tests[i]);
	// 	printf("[%d]============================[%s]\n", i, after_line);
	// }

	// t_parse	pars;
	// char *line = ft_strdup("\'\'\'$USER\'\'\'");
	// char *after_line = process_quotes(&pars, line);
	// printf("line: [%s]\n", line);
	// printf("[%s]\n", after_line);
	return (0);
}