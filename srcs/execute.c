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
		builtin_exit(argv[1]);
	return (NOT_BUILTIN);
}

int		excute_cmd(t_parse *pars, t_list *pipe_lst)
{
	t_exec	*exec_info;
	pid_t	pid;
	char	*cmd;
	int		is_builtin;

	pid = 42;
	is_builtin = FALSE;
	if ((exec_info = redir_process(pars, pipe_lst)) == ERROR)
	{
		print_error(PARSING_ERR, NULL);
		return (ERROR);
	}
	if (exec_info->argv[0])
		is_builtin = execute_builtin(exec_info->argv);
	if (is_builtin == NOT_BUILTIN)
	{
		pid = fork();
		set_process_name(exec_info->argv[0]);
		if (ft_strnstr(exec_info->argv[0], "minishell", ft_strlen(exec_info->argv[0])))
			get_info()->is_minishell = TRUE;
		if (pid == 0)
		{
			cmd = get_cmd(exec_info->argv[0]);
			free(exec_info->argv[0]);
			exec_info->argv[0] = cmd;
			if (execve(cmd, exec_info->argv, get_environ()))
			{
				print_error(COMMAND_ERR, NULL);
				exit(127);
			}
		}
		else if (pid > 0)
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
		else
		{
			print_error(FORK_ERR, NULL);
			return (ERROR);
		}
	}
	close_fds(exec_info);
	free_exec_info(&exec_info);
	return (SUCCESS);
}
