#include "mini.h"

void	print_str(void *str)
{
	ft_putendl_fd((char *)str, 0);
}

int		find_chr(char *str, char ch)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (i);
		i++;
	}
	return (0);
}

char	*free_join(char *s1, char *s2)
{
	int	i;
	int	len1;
	int	len2;
	char *result;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(result = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return(0);
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		result[len1 + i] = s2[i];
		i++;
	}
	result[len1 + len2] = 0;
	free(s1);
	free(s2);
	return (result);
}

void	print_arr(char **arr) // input after pointer calc
{
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (arr + 1 != 0)
			write(1, " ", 1);
		arr++;
	}
}

void	println_arr(char **arr)
{
	while (*arr)
	{
		ft_putstr_fd(*arr, 1);
		if (arr + 1 != 0)
			write(1, "\n", 1);
		arr++;
	}
}

size_t	len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_info *get_info()
{
	static t_info info;
	return &info;
}