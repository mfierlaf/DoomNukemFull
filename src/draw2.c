/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	absolut_coord(t_mlx *mlx, t_draw *draw)
{
	float rtx;
	float rtz;

	rtz = (draw->mapz) * draw->psin - (draw->mapx) * draw->pcos;
	rtx = (draw->mapz) * draw->pcos + (draw->mapx) * draw->psin;
	draw->mapx = rtx + mlx->player.where.x;
	draw->mapz = rtz + mlx->player.where.y;
}

void	map_coord(int screenx, int screeny, t_mlx *mlx, t_draw *draw)
{
	draw->mapz = (draw->mapy) * H * VFOV / ((H / 2 - (screeny)) \
		- mlx->player.yaw * (H * VFOV));
	draw->mapx = (draw->mapz) * (W / 2 - (screenx)) / (W * HFOV);
	absolut_coord(mlx, draw);
}

void	draw_vline(t_mlx *mlx, t_draw *draw, int x)
{
	int cnyb;

	if (draw->neighbor >= 0)
	{
		draw->nya = (x - draw->x1) * (draw->ny2a - draw->ny1a) / \
			(draw->x2 - draw->x1) + draw->ny1a;
		draw->nyb = (x - draw->x1) * (draw->ny2b - draw->ny1b) / \
			(draw->x2 - draw->x1) + draw->ny1b;
		draw->cnya = clamp(draw->nya, draw->ytop[x], draw->ybottom[x]);
		cnyb = clamp(draw->nyb, draw->ytop[x], draw->ybottom[x]);
		vertical_line(draw, new_vl(x, draw->cya, draw->cnya - 1, draw->txtx),
			(t_scaler)scaler_init(new_scale(draw->ya, draw->cya,
							draw->yb, new_point(0, TEXTURE_SIZE - 1))), mlx);
		draw->ytop[x] = clamp(max(draw->cya, draw->cnya), draw->ytop[x], H - 1);
		vertical_line(draw, new_vl(x, cnyb + 1, draw->cyb, draw->txtx),
			(t_scaler)scaler_init(new_scale(draw->ya, cnyb + 1, draw->yb,
				new_point(0, TEXTURE_SIZE - 1))), mlx);
		draw->ybottom[x] = clamp(min(draw->cyb, cnyb), 0, draw->ybottom[x]);
	}
	else
	{
		vertical_line(draw, new_vl(x, draw->cya, draw->cyb, draw->txtx),
			(t_scaler)scaler_init(new_scale(draw->ya, draw->cya,
				draw->yb, new_point(0, TEXTURE_SIZE - 1))), mlx);
	}
}

void	boucle_drawing2(t_mlx *mlx, t_draw *draw, int x, int y)
{
	unsigned	txtx;
	unsigned	txtz;
	int			color;

	txtx = (draw->mapx * 16);
	txtz = (draw->mapz * 16);
	mlx->tex_ternary = y < draw->cya ? \
		mlx->tab_bmp[MOSSY]->data : mlx->tab_bmp[MINECRAFT]->data;
	color = mlx->tex_ternary[(txtx % TEXTURE_SIZE)\
		* TEXTURE_SIZE + (txtz % TEXTURE_SIZE)];
	if (mlx->sectors[draw->now.sectorno].brightness == 0)
		color = (color >> 1) & 8355711;
	if (!mlx->sectors[draw->now.sectorno].sky ||
		mlx->tex_ternary == mlx->tab_bmp[MINECRAFT]->data)
		mlx->data[y * W + x] = color;
	else
	{
		color = mlx->tab_bmp[GATE]->data[(txtx % TEXTURE_SIZE)\
			* TEXTURE_SIZE + (txtz % TEXTURE_SIZE)];
		if (color != FILTER_COLOR)
			mlx->data[y * W + x] = color;
	}
}

void	boucle_drawing(t_mlx *mlx, t_draw *draw, int x)
{
	int			y;

	y = draw->ytop[x] - 1;
	while (++y <= draw->ybottom[x])
	{
		if (y >= draw->cya && y <= draw->cyb)
		{
			y = draw->cyb;
			continue;
		}
		draw->mapy = y < draw->cya ? draw->yceil : draw->yfloor;
		map_coord(x, y, mlx, draw);
		boucle_drawing2(mlx, draw, x, y);
	}
	draw_vline(mlx, draw, x);
	draw_sprites(x, mlx);
	draw_deco(x, mlx);
}
