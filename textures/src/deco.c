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

void				draw_decos(t_draw *draw, int wall, int x, t_mlx *mlx) //DON"T KNOW WHAT SECT IS BEING DRAWN
{
	int					deco;
	int					sector;
	// t_wall_and_sector	ws;
	// float				dist;

	// ws.wall = wall;
	// ws.sector = sect;
	deco = -1;
	sector = -1;
	while (++sector < mlx->num_sectors)
	{
		while (++deco < NB_DECO)
		{
			//Opening gate or door
			// if (mlx->open_door && mlx->inventory.keys && CURR_WALL.is_portal)
			// {
			// 	dist = get_dist(mlx->player.where, CURR_WALL.orig);
			// 	if (dist < 1.5)
			// 	{
			// 		if (mlx->sector[sect].decos[deco].wall_num == wall)
			// 		{
			// 			mlx->sector[sect].decos[deco].moving_offset = 1;
			// 			mlx->inventory.keys--;
			// 			mlx->walls[wall].is_portal = 1;
			// 		}
			// 	}
			// 	else
			// 		mlx->open_door = 0;
			// }
			if (mlx->sectors[sect].decos[deco].wall_num == wall)
				draw_deco(draw, deco, wall, mlx, x);
		}
	}
}

void				draw_deco(t_draw *draw, int deco, int wall,
										t_mlx *mlx, int x)
{
	t_line		decos_pos;
	t_line		walls_pos;
	t_pos		inter;
	// t_draw		d;
	float dist;
	float line_height;
	float draw_start;
	float draw_end;
	t_pos pl_pos;

	walls_pos.orig = draw->sect->wall[wall].orig;
	walls_pos.end = draw->sect->wall[wall].end;

	decos_pos.orig.x = walls_pos.orig.x += (walls_pos.orig.x - walls_pos.end.x) * 0 + 0.0001;
	decos_pos.orig.y = walls_pos.orig.y += (walls_pos.orig.y - walls_pos.end.y) * 0;
	decos_pos.end.x = walls_pos.end.x += (walls_pos.end.x - walls_pos.orig.x) * 0;
	decos_pos.end.y = walls_pos.end.y += (walls_pos.end.y - walls_pos.orig.y) * 0;

	// gate opening
	// if (MAP->sectors[sect].decos[deco].tex == 91 && MAP->sectors[sect].decos[deco].origin_offset < 1 && MAP->sectors[sect].decos[deco].moving_offset == 1)
	// {
	// 	MAP->sectors[sect].decos[deco].origin_offset += 0.00008;
	// 	MAP->sectors[sect].decos[deco].end_offset -= 0.00008;
	// 	if (MAP->sectors[sect].decos[deco].origin_offset >=  0.99)
	// 	{
	// 		mlx->open_door = 0;
	// 		MAP->sectors[sect].decos[deco].moving_offset = 0;
	// 	}
	// }
	inter = get_intersection(mlx->ray, decos_pos,
		get_slope(mlx->ray), get_slope(decos_pos));
	if (!isinf(inter.x))
	{
		// d = draw_deco2(inter, mlx);
		pl_pos.x = mlx->player.where.x;
		pl_pos.y = mlx->player.where.y;
		dist = get_dist(pl_pos, inter);
		dist == 0.0 ? dist = 0.01 : 0;
		line_height = (float)H / dist;
		draw_start = H * 0.5 - line_height * 0.5;
		draw_end = draw_start + line_height;
		vertical_sprite_lines(mlx, x, decos_pos.orig, decos_pos.end,
		draw_start, draw_end, inter,
			mlx->tab_bmp[mlx->sectors[sect].decos[deco].tex]);
	}
}

// t_draw				draw_deco2(t_pos inter, t_mlx *mlx)
// {
// 	t_draw		d;

// 	d.dist = get_dist(mlx->player.where, inter);
// 	d.dist == 0.0 ? d.dist = 0.01 : 0;
// 	d.line_height = (float)H / d.dist;
// 	d.draw_start = H * 0.5 - d.line_height * 0.5;
// 	d.draw_end = d.draw_start + d.line_height;
// 	return (d);
// }

// void				bullet_deco(t_line ray, t_mlx *mlx)
// {
// 	int				wall;
// 	int				sect;
// 	t_pos			inter;
// 	float			offset;

// 	sect = -1;
// 	while (++sect < mlx->map->nb_sectors)
// 	{
// 		wall = -1;
// 		while (++wall < CURR_SECT.nb_walls)
// 		{
// 			inter = get_intersection(ray, new_line(CURR_WALL.orig,
// 				CURR_WALL.end), get_slope(ray), get_slope(new_line(
// 					CURR_WALL.orig, CURR_WALL.end)));
// 			if (!isnan(inter.x) && !CURR_WALL.is_portal)
// 			{
// 				CURR_SECT.decos[0].wall_num = wall;
// 				CURR_SECT.decos[0].tex = 90;
// 				offset = get_dist(inter, CURR_WALL.orig) /
// 				get_dist(CURR_WALL.orig, CURR_WALL.end) + 0.1;
// 				CURR_SECT.decos[0].origin_offset = offset;
// 				CURR_SECT.decos[0].end_offset = 1 - offset;
// 			}
// 		}
// 	}
// }
