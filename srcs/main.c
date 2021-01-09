#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mini.h"
#include "libft.h"

t_exec	*redir_process(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info = NULL;
	t_list	*redirection_lst = NULL;

	if (input_redirection_lst(pars, pipe_lst->content, &redirection_lst))
	{
		exec_info = create_exec(pars, redirection_lst);
	}
	if (exec_info->fd[0] != NULL && exec_info->fd[0][exec_info->input_count - 1] != 0)
	{
		exec_info->std[0] = dup(0);
		dup2(exec_info->fd[0][exec_info->input_count - 1], 0);
	}
	if (exec_info->fd[1] != NULL && exec_info->fd[1][exec_info->output_count - 1] != 0)
	{
		exec_info->std[1] = dup(1);
		dup2(exec_info->fd[1][exec_info->output_count - 1], 1); 
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
		close(exec_info->std[0]);
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
		close(exec_info->std[1]);
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
	int		is_builtin;

	pid = 42;
	is_builtin = FALSE;
	exec_info = redir_process(pars, pipe_lst);
	if (exec_info->argv[0])
		is_builtin = execute_builtin(exec_info->argv);
	if (is_builtin == NOT_BUILTIN)
	{
		pid = fork();
		set_process_name(exec_info->argv[0]);
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
			// if(WIFSIGNALED(status))
			// {
			// 	fprintf(stderr, "error in excute_cmd: [%d]\n", status);
			// 	error();
			// }
		}
		else
		{
			error(FORK_ERROR);
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
		pid = fork();
		get_info()->pid = pid;
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
		excute_cmd(pars, pipe_lst);
		dup2(get_info()->std[1], 1);
		dup2(get_info()->std[0], 0);
		if (pipe_lst->next)
		{
			wait(&status);
			// if(WIFSIGNALED(status))
			// {
			// 	fprintf(stderr, "error in piping: [%d]\n", status);
			// 	error();
			// }
		}
	}
	else
	{
		error(FORK_ERROR);
	}
}

void	print_prompt()
{
	char	*prompt;

	prompt = "C2H5OH$$$ ";
	ft_putstr_fd(prompt, 1);
}

void	interruptHandler(int sig)
{
	if (sig == SIGINT)
	{
		if (get_info()->pid != 0)
			kill(get_info()->pid, sig);
		if (!ft_strcmp(NAME, get_info()->process_name))
		{
			ft_putstr_fd("\b\b  \b\b", 1);
			write(1, "\n", 1);
			print_prompt();
		}
		else if (get_info()->process_index == 1)
			ft_putstr_fd("\n", 2);
	}
	else if (sig == SIGQUIT)
	{
		if (get_info()->pid != 0)
			kill(get_info()->pid, sig);
		if (!ft_strcmp(NAME, get_info()->process_name))
			ft_putstr_fd("\b\b  \b\b", 1);
		else if (get_info()->process_index == 1)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

int		main()
{
	t_parse	pars;
	char	*command;
	t_pro	*pro_lst;
	t_list	*pipe_lst;

	get_info()->env_list = create_env_list();
	get_info()->process_name = NULL;
	signal(SIGINT, interruptHandler);
	signal(SIGQUIT, interruptHandler);
	while (MINISHELL)
	{
		set_process_name(NAME);
		print_prompt();
		get_next_line(0, &command);
		init_pars(&pars);
		main_parse(command, &pars);
		pro_lst = pars.pro_lst;
		get_info()->std[0] = dup(0);
		get_info()->std[1] = dup(1);
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
