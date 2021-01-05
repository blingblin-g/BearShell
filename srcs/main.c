#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mini.h"
#include "libft.h"


void error()
{
	printf("이 코드 나중에 안지우면 큰일남^^\n");
}

t_exec	*redir_process(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info = NULL;
	t_list	*redirection_lst = NULL;

	if (input_redirection_lst(pars, pipe_lst->content, &redirection_lst))
	{
		exec_info = create_exec(pars, redirection_lst);
		// print_exec_info(exec_info);
	}
	// 이거 리디렉션
	if (exec_info->fd[0] != NULL && exec_info->fd[0][exec_info->input_count - 1] != 0)
	{
		exec_info->std[0] = dup(0);
		dup2(exec_info->fd[0][exec_info->input_count - 1], 0); // 입력
	}
	if (exec_info->fd[1] != NULL && exec_info->fd[1][exec_info->output_count - 1] != 0)
	{
		exec_info->std[1] = dup(1);
		dup2(exec_info->fd[1][exec_info->output_count - 1], 1); // 출력
	}
	return (exec_info);
}

void	excute_cmd(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info;
	int		status;
	pid_t	pid;
	char	*cmd;

	pid = 42;
	exec_info = redir_process(pars, pipe_lst);
	if (!execute_builtin(exec_info->argv))
	{
		pid = fork();
		if (pid == 0)
		{
			cmd = get_cmd(exec_info->argv[0]);
			free(exec_info->argv[0]);
			exec_info->argv[0] = cmd;
			execve(cmd, exec_info->argv, get_environ());
		}
		else if (pid > 0)
		{
			wait(&status);
			if(WIFSIGNALED(status))
			{
				error(); // 이 에러는 자식 프로세스가 엄하게 뒤져버려서 생긴 에러
			}
		}
		else
		{
			error(); // 이 에러는 fork가 잘 안돼서 생긴 에러
		}
	}
}

void	piping(t_parse *pars, t_list *pipe_lst)
{
	int		io[2];
	pid_t	pid;
	int		status;

	pid = 42;
	if (pipe_lst->next)
	{
		pipe(io);
		pid = fork();
	}
	if (pid == 0)
	{
		get_info()->std[0] = dup(0);
		get_info()->std[1] = dup(1);
		dup2(0, io[0]);
		piping(pars, pipe_lst->next);
		if (pipe_lst->next->next)
			dup2(io[1], 1);
	}
	else if (pid > 0)
	{
		excute_cmd(pars, pipe_lst);
		if (pipe_lst->next)
		{
			wait(&status);
			if(WIFSIGNALED(status))
			{
				error(); // 이 에러는 자식 프로세스가 엄하게 뒤져버려서 생긴 에러
			}
		}
	}
	else
	{
		error();
	}
}












































// void	pipe_process()
// {
// 	그니까 fd[2] 이러헥 선언해놓고
// 	fd[0인지 1인지 하여튼 둘중 하나에 넣으면 반대쪽에서 텨나오자나여]

// 	original_input = dup(0);
// 	original_output = dup(1);
// 	while (pipe_lst->next)
// 	{
// 		fork() 이렇게 해야겟조
// 		dup2(0, fd[아 그 배열 몇번째인지 생각 안나는데 하여튼 입력받은거를 꺼내는거]);
// 		이렇게 연결을 하는거임
// 		그래서 연결을 했자나요? 그리고 여기에도 출력값이 있겠죠?

// 		dup2(fd[보내는 배열], 1); 네 이렇게 또 마지막에 연결을 해주는거임
// 		사실 직관적으로는 제가 이 처리를 하면서 리디렉션도 같이 해야한다고 생각하는데 지금 졸려서 기억이 잘 안나는데
// 		파이프를 먼저 다 연결 시키고 리디렉션을 햇던걸로 기억함 그래서 일단 대충 써놓고 내일 보강하겠다 ㅎ_ㅎ
// 	}
// 	이거를 반복함
// 	마지막에 파이프가 없어서 텨나왓자나요?
// 	네 input과 output을 멀쩡하게 복구시켜놓고
// 	이제 이 함수 밖에서 pipe리스트를 돌면서 redirection 처리를 하면서 execve나 빌트인을 하면 됩니다!
// 	대충 감이 오시나요? 네
// }

// int		main(void)
// {
// 	t_parse	pars;
// 	char	*command;
// 	char	*prompt;
// 	int		chlid;
// 	int		pid;
// 	t_pro	*pro_lst;
// 	t_list	*pipe_lst;
// 	t_list	*redirection_lst;
// 	t_exec	*exec_info;
// 	char	*real_cmd;
// 	int		state;

// 	while (1)
// 	{
// 		chlid = 27;
// 		ft_putchar_fd(prompt, 1);
// 		get_next_line(0, &command);
// 		init_pars(&pars);
// 		main_parse(command, &pars);
// 		pro_lst = pars.pro_lst;
// 		while (pro_lst)
// 		{
// 			pipe_lst = pro_lst->pipe_lst;
// 			while (pipe_lst)
// 			{
// 				redirection_lst = NULL;
// 				printf("pipe_lst == [%s]\n", (char *)pipe_lst->content);
// 				if (!input_redirection_lst(&pars, pipe_lst->content, &redirection_lst))
// 					return (ERROR);//(~대충 에러나는걸 나타내는 함수~)
// 				exec_info = create_exec(&pars, redirection_lst);
// 				real_cmd = get_cmd(exec_info->argv[0]);
// 				if (is_builtin(real_cmd))
// 				{
					
// 				}
// 				else
// 				{
// 					//execve(exec_info->argv); >v< +0+네 근데 지금 얘가 빌트인일수도 있자나여
// 				}
// 				chlid = fork();
// 				if (chlid == 0)
// 				{
// 					// if (is_builtin(real_cmd))
// 					// 	execve();//하고 이거 뭐 에러 뜨면 그거 받아와서 출력해주는 함수 쓰면 될 것 같고
// 					// else
// 					// 	//(~대충 그 빌트인 찾아서 실행시키는 함수~)
// 				}
// 				else if (chlid > 0)
// 				{
// 					pid = waitpid();

// 				}
// 				else
// 				{
// 					(~대충 에러~)
// 				}
// 				pipe_lst = pipe_lst->next;
// 			}
// 			pro_lst = pro_lst->next;
// 		}
// 	}
// }

void	print_prompt()
{
	char	*prompt;

	prompt = "C2H5OH$$$ ";
	ft_putstr_fd(prompt, 1);
}

int		main()
{
	t_parse	pars;
	char	*command;
	t_pro	*pro_lst;
	t_list	*pipe_lst;

	get_info()->env_list = create_env_list();
	while (MINISHELL)
	{
		print_prompt();
		get_next_line(0, &command);
		init_pars(&pars);
		main_parse(command, &pars);
		pro_lst = pars.pro_lst;
		while (pro_lst)
		{
			pipe_lst = pro_lst->pipe_lst;
			piping(&pars, pipe_lst);
			pro_lst = pro_lst->next;
		}
	}
	return (0);
}
