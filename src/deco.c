/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deco.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <cvan-duf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:53:03 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/10/09 16:34:15 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	draw_deco(int x, t_mlx *mlx)
{
	int		i;
	float	dist;
	float	line_height;
	float	draw_start;
	float	draw_end;
	t_pos	inter;
	t_pos	pl_pos;
	t_line	deco_line;

	i = -1;
	while (++i < NB_DECO)
	{
		deco_line.orig.x = mlx->decos[i].origin.x + 0.0001;
		deco_line.orig.y = mlx->decos[i].origin.y;
		deco_line.end.x = mlx->decos[i].end.x;
		deco_line.end.y = mlx->decos[i].end.y;
		inter = get_intersection(mlx->ray, deco_line,
		get_slope(mlx->ray), get_slope(deco_line));
		if (!isinf(inter.x) && mlx->player.sector == mlx->objects[i].sector)
		{
			pl_pos.x = mlx->player.where.x;
			pl_pos.y = mlx->player.where.y;
			dist = get_dist(pl_pos, inter);
			dist == 0.0 ? dist = 0.01 : 0;
			line_height = (float)H / dist;
			draw_start = H * 0.5 - line_height * 0.5;
			draw_end = draw_start + line_height;
			vertical_sprite_lines(mlx, x, deco_line.orig, deco_line.end,
				draw_start, draw_end, inter,
				mlx->tab_bmp[mlx->decos[i].tex], i);
		}
	}
}
