#include "mini.h"

int		piping(t_parse *pars, t_list *pipe_lst)
{
	int		io[2];
	pid_t	pid;
	int		status;

	pid = 42;
	status = 0;
	if (pipe_lst->next)
	{
		pipe(io);
		pid = fork();
	}
	if (pid == 0)
	{
		set_process_name("pipe");
		close(io[1]);
		dup2(io[0], 0);
		close(io[0]);
		piping(pars, pipe_lst->next);
		exit(0);
	}
	else if (pid > 0)
	{
		if (pipe_lst->next)
		{
			close(io[0]);
			dup2(io[1], 1);
			close(io[1]);
		}
		// 여기 확인함, 누수 없었음
		if (excute_cmd(pars, pipe_lst) == ERROR)// 이새끼가 범인임
			return (ERROR);
		// 여기서 누수 확인됨
		dup2(get_info()->std[1], 1);
		dup2(get_info()->std[0], 0);
		if (pipe_lst->next)
			wait(&status);
	}
	else
	{
		print_error(FORK_ERR, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}