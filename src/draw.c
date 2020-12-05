/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
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
		vertical_line(draw, new_vl(x, cnyb + 1, draw->cyb, draw->txtx), (t_scaler)scaler_init(\
			new_scale(draw->ya, cnyb + 1, draw->yb, new_point(0, TEXTURE_SIZE - 1))), mlx);
		draw->ybottom[x] = clamp(min(draw->cyb, cnyb), 0, draw->ybottom[x]);
	}
	else
	{
		vertical_line(draw, new_vl(x, draw->cya, draw->cyb, draw->txtx),
			(t_scaler)scaler_init(
				new_scale(draw->ya, draw->cya, draw->yb, 
					new_point(0, TEXTURE_SIZE - 1))), mlx);
	}
}

void	boucle_drawing(t_mlx *mlx, t_draw *draw, int x)
{
	unsigned	txtx;
	unsigned	txtz;
	int			y;
	int			color;

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
	draw_vline(mlx, draw, x);
	draw_sprites(x, mlx);
	draw_deco(x, mlx);
}

void	drawing(t_mlx *mlx, t_draw *draw)
{
	int		x;
	int		i;
	t_pos	pl_pos;

	x = draw->beginx - 1;
	draw->ya_int = scaler_init(new_scale(draw->x1, draw->beginx, draw->x2, new_point(draw->y1a, draw->y2a)));
	draw->yb_int = scaler_init(new_scale(draw->x1, draw->beginx, draw->x2, new_point(draw->y1b, draw->y2b)));
	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	i = -1;
	while (++i < NB_OBJ)
	{
		mlx->objects[i].order = i;
		mlx->objects[i].distance = get_dist(pl_pos, mlx->objects[i].pos);
	}
	sort_sprites(mlx);
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
		draw->i1 = intersect(new_pos(draw->tx1, draw->tz1), new_pos(draw->tx2, draw->tz2),\
			new_pos(-nearside, draw->nearz), new_pos(-farside, farz));
		draw->i2 = intersect(new_pos(draw->tx1, draw->tz1), new_pos(draw->tx2, draw->tz2),\
			new_pos(nearside, draw->nearz), new_pos(farside, farz));
		players_view(draw);
	}
}

void	render_declaration(t_mlx *mlx, t_draw *draw, int s)
{
	float	vx1;
	float	vx2;
	float	vy1;
	float	vy2;
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
	draw->u0 = 0;
	draw->u1 = TEXTURE_SIZE - 1;
	vx1 = draw->sect->vertex[s + 0].x - mlx->player.where.x;
	vy1 = draw->sect->vertex[s + 0].y - mlx->player.where.y;
	vx2 = draw->sect->vertex[s + 1].x - mlx->player.where.x;
	vy2 = draw->sect->vertex[s + 1].y - mlx->player.where.y;
	draw->tex = mlx->vert_tex[draw->sect->vert_id[s]];
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
	draw.renderedsectors = malloc(sizeof(int) * mlx->num_sectors);
	while (++x < W)
	{
		draw.ybottom[x] = H - 1;
	}
	while (++n < mlx->num_sectors)
		draw.renderedsectors[n] = 0;
	draw_start(mlx, &draw);
	free_draw(&draw);
}
