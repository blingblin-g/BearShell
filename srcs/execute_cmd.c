#include "mini.h"

int		execute_builtin(char **argv)// 여기서 path랑 argv받아오면 되겟네요
{// 리턴에 함수 옮겨놨고 함수 하나하나 좀 더 정리를 해야함 return 값을 true로 바꾼다거나 살을 좀 더 붙일 것
	printf("argv[0]: [%s], res: [%d]\n", argv[0], ft_strcmp(argv[0], "echo"));
	if (!ft_strcmp(argv[0], "echo"))
		return (echo(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (pwd());
	if (!ft_strcmp(argv[0], "export"))
		return (export(argv[1]));
	if (!ft_strcmp(argv[0], "unset"))
		return (unset(argv[1]));
	if (!ft_strcmp(argv[0], "cd"))
		return (cd(argv[1]));
	if (!ft_strcmp(argv[0], "env"))
		return (env());
	if (!ft_strcmp(argv[0], "exit"))
		free_exit(get_info()->exit_status);
	return (FALSE);
}

// if (input_redirection_lst(&pars, pipe_lst->content, &redirection_lst))
// {
// 	exec_info = create_exec(&pars, redirection_lst);
// 	print_exec_info(exec_info);
// }

// 쟤는 리디렉션 리스트를 만드는거죠
// 네 파일을 다 오픈해서 마지막거를 dup해놓고
// 그 다음에 이 밑에거를 실행시킨다고 생각하고 만들면 될 것 같아요
// pipe()
// fork()
// dup(파이프)
// 싹다 연결 조지고(애비는 리디렉션 조지고 자식은 파이프 조짐)
// 애비가 리디렉션 조지고 나서 할 일:

void	execute_cmd(t_exec *exec_info)
{
	char	*cmd;

	if (!execute_builtin(exec_info->argv))
	{
		cmd = get_cmd(exec_info->argv[0]);
		free(exec_info->argv[0]);
		exec_info->argv[0] = cmd;
		if (exec_info->fd[0][exec_info->fd_input_idx] != 0)
			dup2(exec_info->fd[0][exec_info->fd_input_idx], 0); // 입력
		if (exec_info->fd[1][exec_info->fd_output_idx] != 0)
			dup2(exec_info->fd[1][exec_info->fd_output_idx], 1); // 출력
		if (execve(cmd, exec_info->argv, get_environ()))
		{
			// error();
		}
	}
}

// 이 다음에 할 일:
// 뭐였더라 execve 다음에 연거 다 닫아주고 wait 걸어주고 넹 그럼 끝남!