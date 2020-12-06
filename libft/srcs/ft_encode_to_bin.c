/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encode_to_bin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdelvenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:49:07 by sdelvenn          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:13 by sdelvenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"
#include <fcntl.h>

void	ft_convert_and_write(char *directory, int fp_bin)
{
	char	*octet;

	octet = malloc(9);
	ft_char_to_binary(*directory, octet);
	write(fp_bin, octet, 8);
}

void	ft_encode_to_bin(char *directory)
{
	char	ch;
	int		fp;
	int		fp_bin;

	fp = open(directory, O_RDONLY);
	fp_bin = open("data.bin", O_CREAT | O_WRONLY | O_APPEND);
	if (fp < 0 || fp_bin < 0)
	{
		perror(directory);
		exit(1);
	}
	while (*directory != 0)
	{
		ft_convert_and_write(directory, fp_bin);
		directory++;
	}
	ft_convert_and_write("\n", fp_bin);
	while (read(fp, &ch, 1) > 0)
	{
		ft_convert_and_write(&ch, fp_bin);
	}
	ft_convert_and_write("\n", fp_bin);
	close(fp);
	close(fp_bin);
}
