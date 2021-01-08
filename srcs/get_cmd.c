#include "mini.h"

char	*join_cmd_envpath(char	**path, char *command)
{
	DIR		*dp;
	char	*tmp;
	char	*tmp2;
	int		i;
	t_dir	*file;

	i = 0;
	while (path[i])
	{
		dp = opendir(path[i]);
		while ((file = readdir(dp)))
		{
			if (!ft_strcmp(file->d_name, command))
			{
				tmp = ft_strjoin(path[i], "/");
				tmp2 = ft_strjoin(tmp, command);
				free(tmp);
				return (tmp2);
			}
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd(char *cmd)
{
	char	**path;
	char	*last_slash;

	path = ft_split(get_env_item("PATH"), ':');
	if (path && !(last_slash = ft_strrchr(cmd, '/')))
		return (join_cmd_envpath(path, cmd));
	return (ft_strdup(cmd));
}
