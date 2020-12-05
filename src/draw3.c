/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	check_edge(t_mlx *mlx, t_draw *draw)
{
	float nyceil;
	float nyfloor;

	nyceil = 0;
	nyfloor = 0;
	if (draw->neighbor >= 0)
	{
		nyceil = mlx->sectors[draw->neighbor].ceil - mlx->player.where.z;
		nyfloor = mlx->sectors[draw->neighbor].floor - mlx->player.where.z;
	}
	draw->y1a = H / 2 - (int)(yaw(draw->yceil, draw->tz1, mlx) * draw->yscale1);
	draw->y1b = H / 2 - (int)(yaw(draw->yfloor, draw->tz1, mlx)\
		* draw->yscale1);
	draw->y2a = H / 2 - (int)(yaw(draw->yceil, draw->tz2, mlx) * draw->yscale2);
	draw->y2b = H / 2 - (int)(yaw(draw->yfloor, draw->tz2, mlx)\
		* draw->yscale2);
	draw->ny1a = H / 2 - (int)(yaw(nyceil, draw->tz1, mlx) * draw->yscale1);
	draw->ny1b = H / 2 - (int)(yaw(nyfloor, draw->tz1, mlx) * draw->yscale1);
	draw->ny2a = H / 2 - (int)(yaw(nyceil, draw->tz2, mlx) * draw->yscale2);
	draw->ny2b = H / 2 - (int)(yaw(nyfloor, draw->tz2, mlx) * draw->yscale2);
	draw->beginx = max(draw->x1, draw->now.sx1);
	draw->endx = min(draw->x2, draw->now.sx2);
	drawing(mlx, draw);
}

int		perspective(t_mlx *mlx, t_draw *draw, int s)
{
	float xscale2;
	float xscale1;

	xscale1 = (W * HFOV) / draw->tz1;
	draw->yscale1 = (H * VFOV) / draw->tz1;
	draw->x1 = W / 2 - (int)(draw->tx1 * xscale1);
	xscale2 = (W * HFOV) / draw->tz2;
	draw->yscale2 = (H * VFOV) / draw->tz2;
	draw->x2 = W / 2 - (int)(draw->tx2 * xscale2);
	if (draw->x1 >= draw->x2 || draw->x2 < draw->now.sx1 ||\
			draw->x1 > draw->now.sx2)
		return (1);
	draw->yceil = draw->sect->ceil - mlx->player.where.z;
	draw->yfloor = draw->sect->floor - mlx->player.where.z;
	draw->neighbor = draw->sect->neighbors[s];
	check_edge(mlx, draw);
	return (0);
}

void	players_view_tz2(t_draw *draw)
{
	draw->tx1 = draw->i1.x;
	draw->tz1 = draw->i1.y;
}

void	players_view(t_draw *draw)
{
	if (draw->tz1 < draw->nearz)
	{
		if (draw->i1.y > 0)
		{
			players_view_tz2(draw);
		}
		else
		{
			draw->tx1 = draw->i2.x;
			draw->tz1 = draw->i2.y;
		}
	}
	if (draw->tz2 < draw->nearz)
	{
		if (draw->i1.y > 0)
		{
			draw->tx2 = draw->i1.x;
			draw->tz2 = draw->i1.y;
		}
		else
		{
			draw->tx2 = draw->i2.x;
			draw->tz2 = draw->i2.y;
		}
	}
}
