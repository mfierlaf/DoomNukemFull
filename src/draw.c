/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:58:48 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/26 17:39:40 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	render_declaration(t_mlx *mlx, t_draw *draw, int s)
{
	float	vx1;
	float	vx2;
	float	vy1;
	float	vy2;

	deco_while(mlx);
	draw->u0 = 0;
	draw->u1 = TEXTURE_SIZE - 1;
	vx1 = draw->sect->vertex[s + 0].x - mlx->player.where.x;
	vy1 = draw->sect->vertex[s + 0].y - mlx->player.where.y;
	vx2 = draw->sect->vertex[s + 1].x - mlx->player.where.x;
	vy2 = draw->sect->vertex[s + 1].y - mlx->player.where.y;
	draw->tex = mlx->vert_tex[draw->sect->v_id[s]];
	draw->pcos = mlx->player.anglecos;
	draw->psin = mlx->player.anglesin;
	draw->tx1 = vx1 * draw->psin - vy1 * draw->pcos;
	draw->tz1 = vx1 * draw->pcos + vy1 * draw->psin;
	draw->tx2 = vx2 * draw->psin - vy2 * draw->pcos;
	draw->tz2 = vx2 * draw->pcos + vy2 * draw->psin;
}

void	render(t_mlx *mlx, t_draw *draw)
{
	unsigned s;

	s = -1;
	while (++s < draw->sect->npoints)
	{
		render_declaration(mlx, draw, s);
		if (draw->tz1 <= 0 && draw->tz2 <= 0)
			continue;
		behind_player(draw);
		draw->check = perspective(mlx, draw, s);
		if (draw->check == 0)
		{
			if (draw->neighbor >= 0 && draw->endx >= draw->beginx &&\
				(draw->head + draw->maxqueue + 1 - draw->tail) % draw->maxqueue)
			{
				*draw->head = (t_item) { draw->neighbor,\
					draw->beginx, draw->endx };
				if (++draw->head == draw->queue + draw->maxqueue)
					draw->head = draw->queue;
			}
		}
	}
}

void	draw_start(t_mlx *mlx, t_draw *draw)
{
	*draw->head = (t_item) { mlx->player.sector, 0, W - 1 };
	if (++draw->head == draw->queue + draw->maxqueue)
		draw->head = draw->queue;
	while (draw->head != draw->tail)
	{
		draw->now = *draw->tail;
		if (++draw->tail == draw->queue + draw->maxqueue)
			draw->tail = draw->queue;
		if (draw->renderedsectors[draw->now.sectorno] & 0x21)
			continue;
		++draw->renderedsectors[draw->now.sectorno];
		draw->sect = &mlx->sectors[draw->now.sectorno];
		render(mlx, draw);
		++draw->renderedsectors[draw->now.sectorno];
	}
}

void	draw_screen(t_mlx *mlx)
{
	unsigned	x;
	unsigned	n;
	t_draw		draw;

	x = -1;
	n = -1;
	draw.maxqueue = 32;
	draw.head = draw.queue;
	draw.tail = draw.queue;
	while (++x < W)
	{
		draw.ytop[x] = 0;
	}
	x = -1;
	if ((draw.renderedsectors = malloc(sizeof(int) * mlx->num_sectors)) == NULL)
		kill_mlx("draw_rendered_sectors_malloc fail\n", mlx);
	while (++x < W)
	{
		draw.ybottom[x] = H - 1;
	}
	while (++n < mlx->num_sectors)
		draw.renderedsectors[n] = 0;
	draw_start(mlx, &draw);
	free_draw(&draw);
}
