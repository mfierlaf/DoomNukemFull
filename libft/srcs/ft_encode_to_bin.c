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

void ft_encode_to_bin(char *directory)
{
	
	int read_bytes;
	char ch;
	char *octet = malloc(9);

	FILE* fp = fopen(directory, "r");
	FILE* fp_bin = fopen("data.bin", "a");
	if(!fp || !fp_bin)
	{
		perror(directory);
		exit(1);
	}

	do
	{
		ft_char_to_binary(*directory, octet);
		fwrite(octet, 1, 8, fp_bin);
		directory++;
	}while(*directory != 0);
	
	ft_char_to_binary('\n', octet);
	fwrite(octet, 1, 8, fp_bin);

	do
	{
		read_bytes = fread(&ch, 1,1, fp);
		ft_char_to_binary(ch, octet);
		//printf(" %s\n", octet);
		fwrite(octet, 1, 8, fp_bin);
		//printf("%s", octet);
	}
	while(read_bytes != 0);

	ft_char_to_binary('\n', octet);
	fwrite(octet, 1, 8, fp_bin);
	fwrite(octet, 1, 8, fp_bin);

	fclose(fp);
	fclose(fp_bin);
}