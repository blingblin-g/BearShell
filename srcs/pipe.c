#include "mini.h"

int		piping_parent(t_parse *pars, t_list *pipe_lst, int io[2])
{
	int		result;

	if (pipe_lst->next)
	{
		close(io[0]);
		dup2(io[1], 1);
		close(io[1]);
	}
	result = excute_cmd(pars, pipe_lst);
	dup2(get_info()->std[1], 1);
	dup2(get_info()->std[0], 0);
	if (pipe_lst->next)
		wait(&(get_info()->exit_status));
	return (result);
}

void	piping_chlid(t_parse *pars, t_list *pipe_lst, int io[2])
{
	set_process_name("pipe");
	close(io[1]);
	dup2(io[0], 0);
	close(io[0]);
	piping(pars, pipe_lst->next);
	if (pipe_lst->next && !(pipe_lst->next->next))
		ft_sleep(1);
	exit(get_info()->exit_status >> 8);
}

int		piping(t_parse *pars, t_list *pipe_lst)
{
	int		io[2];
	pid_t	pid;
	int		result;

	pid = 42;
	result = SUCCESS;
	if (pipe_lst->next)
	{
		pipe(io);
		pid = fork();
	}
	if (pid > 0)
		result = piping_parent(pars, pipe_lst, io);
	else if (pid == 0)
		piping_chlid(pars, pipe_lst, io);
	else
		result = print_error(FORK_ERR, NULL);
	return (result);
}