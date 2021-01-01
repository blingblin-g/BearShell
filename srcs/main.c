#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mini.h"
#include "libft.h"

extern char **environ;

void	pipe_process()
{
	그니까 fd[2] 이러헥 선언해놓고
	fd[0인지 1인지 하여튼 둘중 하나에 넣으면 반대쪽에서 텨나오자나여]

	original_input = dup(0);
	original_output = dup(1);
	while (pipe_lst->next)
	{
		fork() 이렇게 해야겟조
		dup2(0, fd[아 그 배열 몇번째인지 생각 안나는데 하여튼 입력받은거를 꺼내는거]);
		이렇게 연결을 하는거임
		그래서 연결을 했자나요? 그리고 여기에도 출력값이 있겠죠?

		dup2(fd[보내는 배열], 1); 네 이렇게 또 마지막에 연결을 해주는거임
		사실 직관적으로는 제가 이 처리를 하면서 리디렉션도 같이 해야한다고 생각하는데 지금 졸려서 기억이 잘 안나는데
		파이프를 먼저 다 연결 시키고 리디렉션을 햇던걸로 기억함 그래서 일단 대충 써놓고 내일 보강하겠다 ㅎ_ㅎ
	}
	이거를 반복함
	마지막에 파이프가 없어서 텨나왓자나요?
	네 input과 output을 멀쩡하게 복구시켜놓고
	이제 이 함수 밖에서 pipe리스트를 돌면서 redirection 처리를 하면서 execve나 빌트인을 하면 됩니다!
	대충 감이 오시나요? 네
}

int		main(void)
{
	t_parse	pars;
	char	*command;
	char	*prompt;
	int		chlid;
	int		pid;
	t_pro	*pro_lst;
	t_list	*pipe_lst;
	t_list	*redirection_lst;
	t_exec	*exec_info;
	char	*real_cmd;
	int		state;

	while (1)
	{
		chlid = 27;
		ft_putchar_fd(prompt, 1);
		get_next_line(0, &command);
		init_pars(&pars);
		main_parse(command, &pars);
		pro_lst = pars.pro_lst;
		while (pro_lst)
		{
			pipe_lst = pro_lst->pipe_lst;
			while (pipe_lst)
			{
				redirection_lst = NULL;
				printf("pipe_lst == [%s]\n", (char *)pipe_lst->content);
				if (!input_redirection_lst(&pars, pipe_lst->content, &redirection_lst))
					return (ERROR);//(~대충 에러나는걸 나타내는 함수~)
				exec_info = create_exec(&pars, redirection_lst);
				real_cmd = get_cmd(exec_info->argv[0]);
				if (is_builtin(real_cmd))
				{
					
				}
				else
				{
					//execve(exec_info->argv); >v< +0+네 근데 지금 얘가 빌트인일수도 있자나여
				}
				chlid = fork();
				if (chlid == 0)
				{
					// if (is_builtin(real_cmd))
					// 	execve();//하고 이거 뭐 에러 뜨면 그거 받아와서 출력해주는 함수 쓰면 될 것 같고
					// else
					// 	//(~대충 그 빌트인 찾아서 실행시키는 함수~)
				}
				else if (chlid > 0)
				{
					pid = waitpid();

				}
				else
				{
					(~대충 에러~)
				}
				pipe_lst = pipe_lst->next;
			}
			pro_lst = pro_lst->next;
		}
	}
}