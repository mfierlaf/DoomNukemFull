/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decode_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:11:51 by mfierlaf          #+#    #+#             */
/*   Updated: 2019/10/11 12:07:45 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"
#include <fcntl.h>

void	ft_decode_one_file(char *line, int *header, int fd)
{
	int j;
	int i;
	int	fp;

	i = 0;
	j = 0;
	fp = open(line, O_CREAT | O_WRONLY);
	while (j < header[i] && get_next_line_bin(fd, &line) > 0)
	{
		while ((*line))
		{
			write(fp, line, 1);
			line++;
		}
		j++;
		write(fp, "\n", 1);
	}
	i++;
	close(fp);
}

void	ft_decode_file(void)
{
	int		fd;
	int		header[20001];
	int		i;
	char	*line;

	i = 0;
	if ((fd = open("./data.bin", O_RDONLY)) < 0)
		exit(1);
	while (get_next_line_bin(fd, &line) > 0 && (*line) && i < 20000)
	{
		header[i] = ft_atoi(line);
		i++;
	}
	header[i] = -1;
	i = 0;
	while (get_next_line_bin(fd, &line) > 0 && header[i] != -1)
	{
		ft_decode_one_file(line, header, fd);
	}
}
