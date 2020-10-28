/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void move_player(t_mlx *mlx, float dx, float dy)
{
	float px;
	float py;
  unsigned s;

  s = -1;
	px = mlx->player.where.x;
	py = mlx->player.where.y;
	/* Check if this movement crosses one of this sector's edges
	 * that have a neighboring sector on the other side.
	 * Because the edge vertices of each sector are defined in
	 * clockwise order, point_side will always return -1 for a point
	 * that is outside the sector and 0 or 1 for a point that is inside.
	 */
	t_sector* sect = &mlx->sectors[mlx->player.sector];
	const struct xy* const vert = sect->vertex;
	while (++s < sect->npoints) //if i put in while there is a glitch
		if (sect->neighbors[s] >= 0
				&& intersect_box(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
				&& point_side(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
		{
			mlx->player.sector = sect->neighbors[s];
			break;
		}

	mlx->player.where.x += dx;
	mlx->player.where.y += dy;
	mlx->player.anglesin = sinf(mlx->player.angle);
	mlx->player.anglecos = cosf(mlx->player.angle);
}
