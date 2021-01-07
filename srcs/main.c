#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mini.h"
#include "libft.h"


void error()
{
	fprintf(stderr, "이 코드 나중에 안지우면 큰일남^^\n");
}

t_exec	*redir_process(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info = NULL;
	t_list	*redirection_lst = NULL;

	if (input_redirection_lst(pars, pipe_lst->content, &redirection_lst))
	{
		exec_info = create_exec(pars, redirection_lst);
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

void	close_fds(t_exec *exec_info)
{
	int		i;

	i = 0;
	if (exec_info->fd[0])
	{
		dup2(exec_info->std[0], 0);
		while (i < exec_info->input_count)
		{
			close(exec_info->fd[0][i]);
			i++;
		}
	}
	i = 0;
	if (exec_info->fd[1])
	{
		dup2(exec_info->std[1], 1);
		while (i < exec_info->output_count)
		{
			close(exec_info->fd[1][i]);
			i++;
		}
	}
}

void	excute_cmd(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info;
	int		status;
	pid_t	pid;
	char	*cmd;

	pid = 42;
	exec_info = redir_process(pars, pipe_lst);
	if (exec_info->argv[0] && !execute_builtin(exec_info->argv))
	{
		pid = fork();
		if (pid == 0)
		{
			fprintf(stderr, "pid: 0\n");
			cmd = get_cmd(exec_info->argv[0]);
			free(exec_info->argv[0]);
			exec_info->argv[0] = cmd;
			execve(cmd, exec_info->argv, get_environ());
			// close_fds(exec_info);
			// fprintf(stderr, "exit [%s]\n", cmd);
			// exit(1);
		}
		else if (pid > 0)
		{
			fprintf(stderr, "pid: 1\n");
			waitpid(pid, &status, WNOHANG);
			fprintf(stderr, "pid: 1 status: [%d]\n", status);
			while (1)
			{
				sleep(1);
				fprintf(stderr, "pid: 2 status: [%d]\n", status);
			}
			// free_exec_info(&exec_info);
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
	close_fds(exec_info);
}

void	piping(t_parse *pars, t_list *pipe_lst)
{
	int		io[2];
	pid_t	pid;
	int		status;

	pid = 42;
	status = 0;
	if (pipe_lst->next)
	{
		pipe(io);
		get_info()->std[0] = dup(0);
		get_info()->std[1] = dup(1);
		pid = fork();
	}
	if (pid == 0)
	{
		dup2(io[0], 0);
		close(io[1]);
		piping(pars, pipe_lst->next);
		// if (pipe_lst->next->next)
		// 	dup2(io[1], 1);
		exit(0);
	}
	else if (pid > 0)
	{
		if (pipe_lst->next)
			dup2(io[1], 1);
		excute_cmd(pars, pipe_lst);
		if (pipe_lst->next)
		{
			fprintf(stderr, "pid: [%d]\n", pid);
			// wait(&status);
			waitpid(pid, &status, WNOHANG);
			if(WIFSIGNALED(status))
			{
				fprintf(stderr, "1111\n");
				error(); // 이 에러는 자식 프로세스가 엄하게 뒤져버려서 생긴 에러
			}
		}
		close(1);
		dup2(get_info()->std[1], 1);
		// while(TRUE)
		// {
			fprintf(stderr, "status: [%d]\n", status);
		// }
		// exit(0);
	}
	else
	{
		error();
	}
}

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
		free_parse(&pars, command);
	}
	return (0);
}
