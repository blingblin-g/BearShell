#include "mini.h"

int		execute_builtin(char **argv)// 여기서 path랑 argv받아오면 되겟네요
{// 리턴에 함수 옮겨놨고 함수 하나하나 좀 더 정리를 해야함 return 값을 true로 바꾼다거나 살을 좀 더 붙일 것
	// printf("argv[0]: [%s], argv[1]: [%s]\n", argv[0], argv[1]);
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