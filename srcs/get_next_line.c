/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyoon <sooyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:22:48 by sooyoon           #+#    #+#             */
/*   Updated: 2020/11/10 22:49:55 by sooyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"

static char		*free_join(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (result == 0)
		return (0);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	free(s1);
	free(s2);
	result[len1 + len2] = 0;
	return (result);
}

static char		*check_nl(char **str, int need_free)
{
	size_t		len;
	char		*tmp;
	char		*end;
	char		*ret;

	len = ft_strlen(*str);
	tmp = *str;
	end = (char *)ft_memchr(tmp, '\n', len);
	if (end)
	{
		*str = ft_strdup(end + 1);
		*end = 0;
		ret = ft_strdup(tmp);
		if (need_free)
			free(tmp);
		return (ret);
	}
	return (0);
}

static int		ft_read(char **rest, char **line, char *buf)
{
	char		*tmp;

	if (*rest == 0)
		*rest = ft_strdup("");
	if ((tmp = check_nl(&buf, 0)))
	{
		*line = free_join(*rest, tmp);
		*rest = buf;
		return (1);
	}
	*rest = free_join(*rest, ft_strdup(buf));
	return (0);
}

int				real_gnl(int fd, char **line)
{
	static char	*rest[256];
	char		buf[BUFFER_SIZE + 1];
	char		*buf_start;
	int			ret;

	buf_start = buf;
	if (rest[fd] == 0)
		rest[fd] = ft_strdup("");
	if (rest[fd] && (*line = check_nl(&rest[fd], 1)))
		return (1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = 0;
		if (ft_read(&rest[fd], line, buf_start) == 1)
			return (1);
	}
	if (ret < 0)
		return (-1);
	if (ret == 0)
	{
		*line = rest[fd];
		rest[fd] = 0;
		return (0);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	return (real_gnl(fd, line));
}
