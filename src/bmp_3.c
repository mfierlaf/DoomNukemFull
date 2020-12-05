/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:37:49 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/06/18 17:30:36 by cvan-duf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static int				check_bmp(t_bmp_header_f header)
{
	if (header.type != 0x4D42 || header.width_px != header.height_px ||
		header.bits_per_pixel != 24)
		return (0);
	return (1);
}

t_bmp					*read_header_bmp(char *file)
{
	int					fd;
	t_bmp_header		tmp;
	t_bmp_header_f		header;
	t_bmp				*bmp;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (read(fd, &tmp, sizeof(t_bmp_header)) == -1)
		return (NULL);
	if (close(fd))
		return (NULL);
	header = convert_to_header(tmp);
	if (!check_bmp(header))
		return (NULL);
	bmp = read_img_bmp(file, header);
	return (bmp);
}

void					valid_anim(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < ANIM_NB)
	{
		if (!mlx->tab_anim[i])
		{
			i = -1;
			while (++i < ANIM_NB)
			{
				free(mlx->tab_anim[i]);
			}
			kill_mlx("fail in load bmp anim\n", mlx);
		}
	}
}

void					valid_bmp(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < DIFF_BMP)
	{
		if (!mlx->tab_bmp[i])
		{
			i = -1;
			while (++i < DIFF_BMP)
			{
				free(mlx->tab_bmp[i]);
			}
			kill_mlx("fail in load bmp\n", mlx);
		}
	}
	valid_anim(mlx);
}
