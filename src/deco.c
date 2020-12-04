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

static t_line	get_deco_line(int i, t_mlx *mlx)
{
	t_line deco_line;

	deco_line.orig.x = mlx->decos[i].origin.x + 0.0001;
	deco_line.orig.y = mlx->decos[i].origin.y;
	deco_line.end.x = mlx->decos[i].end.x;
	deco_line.end.y = mlx->decos[i].end.y;
	return (deco_line);
}

void			draw_deco(int x, t_mlx *mlx)
{
	int			i;
	t_sprites	deco;

	i = -1;
	while (++i < NB_DECO)
	{
		deco.deco_line = get_deco_line(i, mlx);
		deco.inter = get_intersection(mlx->ray, deco.deco_line,
		get_slope(mlx->ray), get_slope(deco.deco_line));
		if (!isinf(deco.inter.x) && (int)mlx->player.sector ==
			mlx->decos[i].sector)
		{
			deco.pl_pos.x = mlx->player.where.x;
			deco.pl_pos.y = mlx->player.where.y;
			deco.dist = get_dist(deco.pl_pos, deco.inter);
			deco.dist == 0.0 ? deco.dist = 0.01 : 0;
			deco.line_height = (float)H / deco.dist;
			deco.draw_start = H * 0.5 - deco.line_height * 0.5;
			deco.draw_end = deco.draw_start + deco.line_height;
			deco.curr_bmp = mlx->tab_bmp[mlx->decos[i].tex];
			deco.a = deco.deco_line.orig;
			deco.b = deco.deco_line.end;
			vertical_sprite_lines(mlx, x, deco, i);
		}
	}
}
