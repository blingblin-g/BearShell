#include "mini.h"

int		redirection(t_pro *pro)
{
	t_pro	*tmp;
	int		fd[file 개수];
	int		pid;

	tmp = pro;
	while (tmp->next)
	{fd배열을 만들어서 while문을 돌리면서 처리해준다
		if (tmp->type == OUTPUT)
		{
			fd = open(pro->cmd_lst->content, O_RDWR | O_CREAT);
			dup2(fd, 1);
		}
		else if (tmp->type == INPUT)
		{
			fd = open(pro->cmd_lst->content, O_RDWR | O_APPEND);
			dup2(fd, 0);
		}
		else if (tmp->type == APPEND)
		{
			fd = open(pro->cmd_lst->content, O_RDWR | O_CREAT | O_APPEND);
			dup2(fd, 1);
		}
		else
		{
			break ;
		}
		
		tmp = tmp->next;
	}
}

void	new_process(t_pro *pro)
{
	int		pi[2];
	int		pid;
	t_pro	*tmp;

	tmp = pro;
	pipe(pi);
	세미콜론->파이프->리디렉션 순으로 처리하는걸로!
	자매들 어떻게 통신 시킬 것인지?
	마지막에 닫는 것도 생각해주고(리디렉션)
	파싱한 것을 어떻게 이용할 것인지?
	파싱한 것을 trim해주는 방향으로 가야할 것 같다.
	그러면 제가 로직을
	아침~저녁(채욱시 회의전)까지 미니셸? 2~3시간정도 일요일: 2시 반에 떠나기 때문에 1시 반 전까지
	월요일 한강 가따와서 마무리 하는걸로

	pid = fork();
	if (pid == 0)
	{
		자식새끼;
		만약에 built-in : 그거 실행
		else execve 채욱씨가 만들 배열을 넣어서
		에러는 그 안에서 받아오고
		dup2(pi[1], 1);
	}
	else if (pid > 0)
	{
		엄마;
		waitpid(pid, &stat, WNOHANG);
	}
	else
	{
		에러;
	}
	
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			pipe(bayol);
		}
		if (tmp->type == SEMI)
		{
			pid = fork();
		}
	}
}