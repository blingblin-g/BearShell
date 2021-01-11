#include "mini.h"

void	free_parse(t_parse *parse, char *command)
{
	free(command);
	free_prolst(&parse->pro_lst);
	free(parse->line);
}

void	free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = 0;
		i++;
	}
	free(arr);
}

void	free_exec_info(t_exec **exec_info)
{
	int		i;

	i = 0;
	free((*exec_info)->fd[0]);
	free((*exec_info)->fd[1]);
	while ((*exec_info)->argv[i])
	{
		free((*exec_info)->argv[i]);
		i++;
	}
	free((*exec_info)->argv);
}