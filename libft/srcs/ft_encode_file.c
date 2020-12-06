/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:11:51 by mfierlaf          #+#    #+#             */
/*   Updated: 2019/10/11 12:07:45 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"
#include <fcntl.h>

void	ft_creat_header(char *line, char *octet, int fp_bin)
{
	char	*nb_line;

	nb_line = ft_itoa(ft_file_size_line(line));
	while (*nb_line != 0)
	{
		ft_char_to_binary(*nb_line, octet);
		write(fp_bin, octet, 8);
		nb_line++;
	}
	ft_char_to_binary('\n', octet);
	write(fp_bin, octet, 8);
}

void	ft_encode_file(void)
{
	int		fd;
	char	*line;
	char	*octet;
	int		fp_bin;

	octet = ft_memalloc(9);
	fp_bin = open("data.bin", O_TRUNC | O_WRONLY | O_APPEND);
	if (fp_bin < 0)
		exit(1);
	if ((fd = open("./file_listing.txt", O_RDONLY)) < 0)
		exit(1);
	while (get_next_line(fd, &line) > 0)
		ft_creat_header(line, octet, fp_bin);
	ft_char_to_binary('\n', octet);
	write(fp_bin, octet, 8);
	lseek(fd, 0, SEEK_SET);
	lseek(fp_bin, 0, SEEK_END);
	while (get_next_line(fd, &line) > 0)
	{
		ft_encode_to_bin(line);
	}
	close(fp_bin);
}
