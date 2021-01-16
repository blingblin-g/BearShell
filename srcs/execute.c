#include "mini.h"

int		execute_builtin(char **argv)
{
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
		return (builtin_exit(argv));
	return (NOT_BUILTIN);
}

void	excute_cmd_chlid(t_exec *exec_info)
{
	char	*cmd;

	cmd = get_cmd(exec_info->argv[0]);
	free(exec_info->argv[0]);
	exec_info->argv[0] = cmd;
	if (execve(cmd, exec_info->argv, get_environ()))
	{
		print_error(COMMAND_ERR, NULL);
		exit(127);
	}
}

void	execute_cmd_parent(t_list *pipe_lst)
{
	wait(&(get_info()->exit_status));
	if (pipe_lst->next == NULL)
	{
		if (WIFEXITED(get_info()->exit_status))
			get_info()->exit_status = WEXITSTATUS(get_info()->exit_status) << 8;
		else if (WIFSIGNALED(get_info()->exit_status))
			get_info()->exit_status = (WTERMSIG(get_info()->exit_status) + 128) << 8;
		else
			get_info()->exit_status = get_info()->exit_status << 8;
	}
	get_info()->is_minishell = FALSE;
}

int		not_builtin_iter(t_exec	*exec_info, t_list *pipe_lst, int *pid)
{
	*pid = fork();
	set_process_name(exec_info->argv[0]);
	if (ft_strnstr(exec_info->argv[0], "minishell", ft_strlen(exec_info->argv[0])))
		get_info()->is_minishell = TRUE;
	if (*pid == 0)
		excute_cmd_chlid(exec_info);
	else if (*pid > 0)
		execute_cmd_parent(pipe_lst);
	else
	{
		print_error(FORK_ERR, NULL);
		return (ERROR);
	}
	return (SUCCESS);
}

int		excute_cmd(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info;
	pid_t	pid;
	int		is_builtin;

	pid = 42;
	is_builtin = FALSE;
	if ((exec_info = redir_process(pars, pipe_lst)) == ERROR)
		return (print_error(PARSING_ERR, NULL));
	if (exec_info->argv[0])
		is_builtin = execute_builtin(exec_info->argv);
	if (is_builtin == NOT_BUILTIN)
	{
		if (not_builtin_iter(exec_info, pipe_lst, &pid) == ERROR)
			return (ERROR);
	}
	close_fds(exec_info);
	free_exec_info(&exec_info);
	return (SUCCESS);
}
