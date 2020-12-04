/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:29:05 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/06/18 17:25:14 by cvan-duf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

t_bmp				*new_bmp(char *str)
{
	t_bmp			*bmp;

	bmp = read_header_bmp(str);
	return (bmp);
}

int					get_color(t_bmp *bmp, int x, int y)
{
	return (bmp->data[x + y * bmp->header.width_px]);
}

int					check_tab_bmp(t_mlx *mlx)
{
	int				i;

	i = 0;
	while (i < DIFF_BMP)
	{
		if (!mlx->tab_bmp[i])
			return (-1);
		i++;
	}
	return (1);
}

int					read_color_vertical(t_bmp *bmp, int x, int y,
		unsigned char *data)
{
	int				color;
	int				width;
	int				offset;
	int				padding;
	t_color			color_t;

	padding = bmp->header.padding;
	width = bmp->header.width_px;
	offset = bmp->header.offset;
	x *= 3;
	color = (int)data[x + (bmp->header.height_px - 1 - y) * width * 3 +
					offset + (bmp->header.height_px - 1 - y) * padding];
	color_t.off_b = color * 0x1;
	x++;
	color = (int)data[x + (bmp->header.height_px - 1 - y) * width * 3 +
					offset + (bmp->header.height_px - 1 - y) * padding];
	color_t.off_g = color * 0x100;
	x++;
	color = (int)data[x + (bmp->header.height_px - 1 - y) * width * 3 +
					offset + (bmp->header.height_px - 1 - y) * padding];
	color_t.off_r = color * 0x10000;
	return (color_t.off_r + color_t.off_g + color_t.off_b);
}
