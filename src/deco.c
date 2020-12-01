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

void				draw_decos(int wall, int sect, int x, t_mlx *mlx)
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
		while (++deco < mlx->nb_deco)
		{
			//Opening gate or door
			// if (mlx->open_door && mlx->inventory.keys && CURR_WALL.is_portal)
			// {
			// 	dist = get_dist(mlx->player->pos, CURR_WALL.origin);
			// 	if (dist < 1.5)
			// 	{
			// 		if (mlx->deco[deco].wall_num == wall)
			// 		{
			// 			mlx->deco[deco].moving_offset = 1;
			// 			mlx->inventory.keys--;
			// 			mlx->walls[wall].is_portal = 1;
			// 		}
			// 	}
			// 	else
			// 		mlx->open_door = 0;
			// }
			if (mlx->deco[deco].wall_num == wall)
				draw_deco(deco, wall, sect, mlx, x);
		}
	}
}

void				draw_deco(int deco, wall, sect,
										t_mlx *mlx, int x)
{
	t_line		decos_pos;
	t_line		walls_pos;
	t_pos		inter;
	// t_draw		d;

	walls_pos.orig = mlx->sectors[sect].walls[wall].origin;
	walls_pos.end = mlx->sectors[sect].walls[wall].end;

	decos_pos.orig.x = walls_pos.orig.x += (walls_pos.orig.x - walls_pos.end.x) * -mlx->sectors[sect].deco[deco].origin_offset + 0.0001;
	decos_pos.orig.y = walls_pos.orig.y += (walls_pos.orig.y - walls_pos.end.y) * -mlx->sectors[sect].deco[deco].origin_offset;
	decos_pos.end.x = walls_pos.end.x += (walls_pos.end.x - walls_pos.orig.x) * -mlx->sectors[sect].deco[deco].end_offset;
	decos_pos.end.y = walls_pos.end.y += (walls_pos.end.y - walls_pos.orig.y) * -mlx->sectors[sect].deco[deco].end_offset;

	// gate opening
	// if (MAP->sectors[sect].deco[deco].tex == 91 && MAP->sectors[sect].deco[deco].origin_offset < 1 && MAP->sectors[sect].deco[deco].moving_offset == 1)
	// {
	// 	MAP->sectors[sect].deco[deco].origin_offset += 0.00008;
	// 	MAP->sectors[sect].deco[deco].end_offset -= 0.00008;
	// 	if (MAP->sectors[sect].deco[deco].origin_offset >=  0.99)
	// 	{
	// 		mlx->open_door = 0;
	// 		MAP->sectors[sect].deco[deco].moving_offset = 0;
	// 	}
	// }
	inter = get_intersection(mlx->ray, decos_pos,
		get_slope(mlx->ray), get_slope(decos_pos));
	if (!isinf(inter.x))
	{
		// d = draw_deco2(inter, mlx);
		dist = get_dist(mlx->player->pos, inter);
		dist == 0.0 ? d.dist = 0.01 : 0;
		line_height = (float)IMG_H / d.dist;
		draw_start = IMG_H * 0.5 - d.line_height * 0.5;
		draw_end = d.draw_start + d.line_height;
		vertical_sprite_lines(mlx, x, decos_pos.orig, decos_pos.end,
		d.draw_start, d.draw_end, inter,
			mlx->tab_sprite[mlx->sectors[sect].deco[deco].tex]);
	}
}

// t_draw				draw_deco2(t_pos inter, t_mlx *mlx)
// {
// 	t_draw		d;

// 	d.dist = get_dist(mlx->player->pos, inter);
// 	d.dist == 0.0 ? d.dist = 0.01 : 0;
// 	d.line_height = (float)IMG_H / d.dist;
// 	d.draw_start = IMG_H * 0.5 - d.line_height * 0.5;
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
// 			inter = get_intersection(ray, new_line(CURR_WALL.origin,
// 				CURR_WALL.end), get_slope(ray), get_slope(new_line(
// 					CURR_WALL.origin, CURR_WALL.end)));
// 			if (!isnan(inter.x) && !CURR_WALL.is_portal)
// 			{
// 				CURR_SECT.deco[0].wall_num = wall;
// 				CURR_SECT.deco[0].tex = 90;
// 				offset = get_dist(inter, CURR_WALL.origin) /
// 				get_dist(CURR_WALL.origin, CURR_WALL.end) + 0.1;
// 				CURR_SECT.deco[0].origin_offset = offset;
// 				CURR_SECT.deco[0].end_offset = 1 - offset;
// 			}
// 		}
// 	}
// }
