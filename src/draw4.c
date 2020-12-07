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

void	drawing2(t_mlx *mlx, t_draw *draw)
{
	int		i;
	t_pos	pl_pos;

	draw->ya_int = scaler_init(new_scale(draw->x1, draw->beginx,
		draw->x2, new_point(draw->y1a, draw->y2a)));
	draw->yb_int = scaler_init(new_scale(draw->x1, draw->beginx,
		draw->x2, new_point(draw->y1b, draw->y2b)));
	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	i = -1;
	while (++i < NB_OBJ)
	{
		mlx->objects[i].order = i;
		mlx->objects[i].distance = get_dist(pl_pos, mlx->objects[i].pos);
	}
	sort_sprites(mlx);
}

void	drawing(t_mlx *mlx, t_draw *draw)
{
	int		x;

	x = draw->beginx - 1;
	drawing2(mlx, draw);
	while (++x <= draw->endx)
	{
		if (mlx->sectors[draw->now.sectorno].sky &&
			draw->now.sectorno == (int)mlx->player.sector)
			draw_skybox(mlx, x);
		draw->txtx = (draw->u0 * ((draw->x2 - x) * draw->tz2) + draw->u1 *\
			((x - draw->x1) * draw->tz1)) / ((draw->x2 - x) * draw->tz2 +\
				(x - draw->x1) * draw->tz1);
		draw->ya = scaler_next(&draw->ya_int);
		draw->yb = scaler_next(&draw->yb_int);
		draw->cya = clamp(draw->ya, draw->ytop[x], draw->ybottom[x]);
		draw->cyb = clamp(draw->yb, draw->ytop[x], draw->ybottom[x]);
		boucle_drawing(mlx, draw, x);
	}
}

void	behind_player(t_draw *draw)
{
	float farz;
	float nearside;
	float farside;

	if (draw->tz1 <= 0 || draw->tz2 <= 0)
	{
		farz = 5;
		nearside = 1e-5f;
		farside = 20.f;
		draw->nearz = 1e-4f;
		draw->i1 = intersect(new_pos(draw->tx1, draw->tz1),
			new_pos(draw->tx2, draw->tz2),
			new_pos(-nearside, draw->nearz),
			new_pos(-farside, farz));
		draw->i2 = intersect(new_pos(draw->tx1, draw->tz1),
			new_pos(draw->tx2, draw->tz2),
			new_pos(nearside, draw->nearz), new_pos(farside, farz));
		players_view(draw);
	}
}

void	deco_while(t_mlx *mlx)
{
	int		i;

	i = -1;
	while (++i < NB_DECO)
	{
		mlx->decos[i].origin.x =
		mlx->sectors[mlx->decos[i].sector].vertex[mlx->decos[i].wall].x
		- mlx->player.where.x;
		mlx->decos[i].origin.y =
		mlx->sectors[mlx->decos[i].sector].vertex[mlx->decos[i].wall].y
		- mlx->player.where.y;
		mlx->decos[i].end.x =
		mlx->sectors[mlx->decos[i].sector].vertex[mlx->decos[i].wall + 1].x
		- mlx->player.where.x;
		mlx->decos[i].end.y =
		mlx->sectors[mlx->decos[i].sector].vertex[mlx->decos[i].wall + 1].y
		- mlx->player.where.y;
	}
}
