#include "mini.h"
#include <signal.h>
#include <errno.h>

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

void	interruptHandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("this program will be exited...\n");
		exit(0);
	}
	else if (sig == SIGQUIT)
	{
		printf("SIGQUIT!!!!!!\n");
		exit(0);
	}
}

int main(void)
{
	t_parse pars;
	pid_t	child;
	int		status;
	t_list	*redirection_lst = NULL;
	t_exec	*exec_info;

	get_info()->env_list = create_env_list();
	// char *line = ft_strdup("$PWD     $: $ $/  'haha' you s'o    beautifu'l  $PWD");
	// char *line = ft_strdup("            e'ch'o haha' you' fool | echo m\"ero\"ng > result.txt ; cat result.txt | cat -e");
	// char *line = ft_strdup("dobule \'\"\'sq_in_dq\"\'\"dq_in_sq\"\\abc\\haha\\\\sooyoon$chlim$chlim$1haha $\\ $; $+ $?\"earlose tear\"$chlim\"lose");
	// char *line = ft_strdup("\"$\"");
	// char *line = ft_strdup("echo '$chlim' $chlim \\|test ;>chlim echo test >><><><<<<<<>> echo redirection<echo input > echo output < merong < chlim << haha");
	// char *line = ft_strdup("fairy $\\$ \\$chlim echo : \"haha\"yo u 'ba'b o>\\<> hehe test > sooyoon > sooyoon >sooyoon");
	// char *line = ft_strdup("echo test | cat");
	// char *line = ft_strdup("echo test| echo test> sample ; cat | cat | cat");
	// char *line = ft_strdup("echo haha > mkdir yoyo abc > mkdir2 hehe haha");
	// char *line = ft_strdup("echo haha yoyo abc hehe haha > mkdir > mkdir2");
	char *line = ft_strdup("");

	// int cmd_size;
	// int pro_size;
	// t_parse pars; 이게 지금 지역변수로 선언돼있어서
	// 먼저 세미콜론으로 파싱 => 세미리스트(지금은 pro_lst로 되있음) => | 파싱 => 파이프리스트
	// => 파이프 리스트 안에 있는 리디렉션 처리 => 파이프 리스트는 실행시에 동시 실행되야함
	// => 세미리스트는 그냥 순차적으로 실행

	init_pars(&pars);
	// pars.pro_lst->next = NULL;
	printf("line: [%s]\n", line);
	main_parse(line, &pars);
	if (input_redirection_lst(&pars, line, &redirection_lst))
	{
		exec_info = create_exec(&pars, redirection_lst);
		print_exec_info(exec_info);
	}

	child = fork();
	if (child == 0)
	{
		printf("\n-----------------test-------------\n");
		execute_cmd(exec_info);
		printf("\n-----------------test-------------\n");
		exit(0);
	}
	else if (child > 0)
	{
		printf("parent!!! wait pid: [%d]\n", child);
		wait(&status);
		printf("child status: [%d]\n", status);
	}


	// print_prolst(pars.pro_lst); // only 4 test
	// pro_size = prolst_size(pars.pro_lst);
	// printf("pro_size: [%d]\n", pro_size);


	// char	**env_arr = get_environ();

	// for(int i = 0; env_arr[i]; i++)
	// {
	// 	printf("env_arr[%d]: %s\n", i, env_arr[i]);
	// }

	// signal(SIGINT, interruptHandler);
	// signal(SIGQUIT, interruptHandler);
	// while(1);
	// cmd_size = cmdlst_size();
	return (0);
}