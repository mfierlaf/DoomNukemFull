/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jreynaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:15:43 by jreynaer          #+#    #+#             */
/*   Updated: 2020/01/24 15:57:52 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void			skybox_loop(t_mlx *mlx, int x, t_pos *tex)
{
	int				y;

	y = -1;
	while (++y < H)
	{
		tex->y = (mlx->tab_bmp[SKY]->header.height_px * y) / H;
		if (valid_pixel(x, y) && tex->x >= 0 && tex->y >= 0 &&
				tex->x < mlx->tab_bmp[SKY]->header.width_px &&
				tex->y < mlx->tab_bmp[SKY]->header.height_px)
			mlx->data[x + y * W] =
				get_color(mlx->tab_bmp[SKY], tex->x, tex->y);
	}
}

void				draw_skybox(t_mlx *mlx, int x)
{
	t_pos			tex;
	float			angle;
	t_pos			off;

	// angle = -atan2(mlx->player->dir.x, mlx->player->dir.y);
	angle = -atan2(mlx->player.anglesin, mlx->player.anglecos);
	off.x = (mlx->tab_bmp[SKY]->header.width_px * angle) / M_PI;
	tex.x = (mlx->tab_bmp[SKY]->header.width_px * x) /
			(W * M_PI) + off.x;
	if (tex.x < 0)
		tex.x += mlx->tab_bmp[SKY]->header.width_px;
	if (tex.x >= mlx->tab_bmp[SKY]->header.width_px)
		tex.x -= mlx->tab_bmp[SKY]->header.width_px;
	skybox_loop(mlx, x, &tex);
}
