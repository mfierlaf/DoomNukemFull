/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:39:17 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/06/18 17:25:38 by cvan-duf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void					*free_bmp(t_bmp *bmp, int *data, unsigned char *tmp)
{
	if (tmp)
		free(tmp);
	if (data)
		free(data);
	if (bmp)
		free(bmp);
	return (NULL);
}

static t_bmp			*read_img_bmp_2(t_bmp *bmp, t_bmp_header_f header,
		unsigned char *tmp, int fd)
{
	int					i;
	int					j;

	j = 0;
	while (j < header.width_px)
	{
		i = 0;
		while (i < header.height_px)
		{
			bmp->data[i + j * header.width_px] =
					read_color_vertical(bmp, i, j, tmp);
			i++;
		}
		j++;
	}
	free(tmp);
	if (close(fd))
	{
		free(bmp->data);
		free(bmp);
		return (NULL);
	}
	return (bmp);
}

t_bmp					*read_img_bmp(char *file, t_bmp_header_f header)
{
	t_bmp				*bmp;
	int					fd;
	int					size;
	unsigned char		*tmp;

	fd = open(file, O_RDONLY);
	size = header.size;
	if (!(bmp = malloc(sizeof(t_bmp))))
		return (NULL);
	if (!(bmp->data = malloc(sizeof(int) * size)))
		return (free_bmp(bmp, NULL, NULL));
	if (!(tmp = malloc(sizeof(unsigned char) * size)))
		return (free_bmp(bmp, bmp->data, NULL));
	if (read(fd, tmp, size) == -1)
		return (free_bmp(bmp, bmp->data, tmp));
	bmp->header = header;
	return (read_img_bmp_2(bmp, header, tmp, fd));
}

int						convert_to_32(uint16_t left, uint16_t right)
{
	return ((int)(right * 0x10000 + left));
}

t_bmp_header_f			convert_to_header(t_bmp_header src)
{
	t_bmp_header_f		header;

	header.type = (int)src.type;
	header.size = convert_to_32(src.size_1, src.size_2);
	header.reserved1 = src.reserved1;
	header.reserved2 = src.reserved2;
	header.offset = convert_to_32(src.offset1, src.offset2);
	header.dib_header_size = convert_to_32(src.dib_header_size1,
		src.dib_header_size2);
	header.width_px = convert_to_32(src.width_px1, src.width_px2);
	header.height_px = convert_to_32(src.height_px1, src.height_px2);
	header.num_planes = src.num_planes;
	header.bits_per_pixel = src.bits_per_pixel;
	header.compression = convert_to_32(src.compression1, src.compression2);
	header.image_size_bytes = convert_to_32(src.image_size_bytes1,
											src.image_size_bytes2);
	header.x_res = convert_to_32(src.x_resolution_ppm1, src.x_resolution_ppm2);
	header.y_res = convert_to_32(src.y_resolution_ppm1, src.y_resolution_ppm2);
	header.num_colors = convert_to_32(src.num_colors1, src.num_colors2);
	header.important_colors = convert_to_32(src.important_colors1,
											src.important_colors2);
	header.padding = (header.width_px * 6) % 8 / 2;
	return (header);
}
