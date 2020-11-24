/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdelvenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:49:07 by sdelvenn          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:13 by sdelvenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static size_t	find_eol(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

static int		split_s(char **s)
{
	char *tmp;

	tmp = *s;
	if (ft_strchr(*s, '\n'))
	{
		*s = ft_strdup(ft_strchr(tmp, '\n') + 1);
		ft_strdel(&tmp);
		return (0);
	}
	if (find_eol(tmp) > 0)
	{
		*s = ft_strnew(0);
		ft_strdel(&tmp);
		return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	char		*tmp;
	char		buff[BUFF_SIZE + 1];
	int			read_len;

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0 ||
			(!s[fd] && !(s[fd] = ft_strnew(0))))
		return (-1);
	while (!ft_strchr(s[fd], '\n') && (read_len = read(fd, buff, BUFF_SIZE)))
	{
		buff[read_len] = '\0';
		tmp = s[fd];
		if (!(s[fd] = ft_strjoin(tmp, buff)))
			return (-1);
		ft_strdel(&tmp);
	}
	if (!(*line = ft_strsub(s[fd], 0, find_eol(s[fd]))))
		return (-1);
	if (split_s(&s[fd]))
	{
		ft_strdel(line);
		return (0);
	}
	return (1);
}

int				get_next_line_bin(const int fd, char **line)
{
	static char	*s[FOPEN_MAX];
	char		*tmp;
	char		buff[9];
	int			read_len;
	char		*tmp2;

	if (fd < 0 || BUFF_SIZE < 1 || !line || read(fd, buff, 0) < 0 ||
			(!s[fd] && !(s[fd] = ft_strnew(0))))
		return (-1);
	while (!ft_strchr(s[fd], '\n') && (read_len = read(fd, buff, 8)))
	{
		tmp2 = buff;
		ft_binary_to_string(&tmp2, buff);
		buff[read_len] = '\0';
		tmp = s[fd];
		if (!(s[fd] = ft_strjoin(tmp, tmp2)))
			return (-1);
		ft_strdel(&tmp);
	}
	if (!(*line = ft_strsub(s[fd], 0, find_eol(s[fd]))))
		return (-1);
	if (split_s(&s[fd]))
	{
		ft_strdel(line);
		return (0);
	}
	return (1);
}
