#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "mini.h"
#include "libft.h"

extern char **environ;

int		main(void)
{
	char	*command;
	char	**new_argv;
	char	*prompt = "C2H5OH";
	pid_t	child;
	pid_t	pid;
	int		state;
	
	// prompt = make_prompt(environ);
	child = 1;
	while (1)
	{
		if (child == 0)
		{
			if (execve(command, new_argv, environ) == -1)
			{
				fprintf(stderr, "error: haha! %s\n", strerror(errno));
				return (1);
			}
		}
		if (child != 0)
		{
			write(1, prompt, ft_strlen(prompt));
			write(1, "% ", 2);
			get_next_line(1, &command);
			new_argv = ft_split(command, ' ');
			free(command);
			command = new_argv[0];
			child = fork();
			pid = wait(&state);
		}
	}
}