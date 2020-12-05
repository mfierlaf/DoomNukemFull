/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void	game_falling(t_mlx *mlx, t_expose ex)
{
	if (!mlx->flying)
		mlx->player.velocity.z -= JUMP_SPEED;
	ex.nextz = mlx->player.where.z + mlx->player.velocity.z;
	if (mlx->player.velocity.z < 0 && ex.nextz
			< mlx->sectors[mlx->player.sector].floor + ex.eyeheight)
	{
		mlx->player.where.z =
			mlx->sectors[mlx->player.sector].floor + ex.eyeheight;
		mlx->player.velocity.z = 0;
		mlx->falling = 0;
		mlx->ground = 1;
	}
	else if (mlx->player.velocity.z >
			0 && ex.nextz > mlx->sectors[mlx->player.sector].ceil)
	{
		mlx->player.velocity.z = 0;
		mlx->falling = 1;
	}
	if (mlx->falling)
	{
		mlx->player.where.z += mlx->player.velocity.z;
		mlx->moving = 1;
	}
}

static void	game_moving2(t_mlx *mlx, t_expose ex)
{
	ex.hole_low = ex.sect->neighbors[ex.s] < 0 ? 9e9 :
		max(ex.sect->floor,
				mlx->sectors[ex.sect->neighbors[ex.s]].floor);
	ex.hole_high = ex.sect->neighbors[ex.s] < 0 ? -9e9 :
		min(ex.sect->ceil,
				mlx->sectors[ex.sect->neighbors[ex.s]].ceil);
	if (ex.hole_high < mlx->player.where.z + HEADMARGIN
			|| ex.hole_low > mlx->player.where.z -
			ex.eyeheight + KNEEHEIGHT)
	{
		ex.xd = ex.vert[ex.s + 1].x - ex.vert[ex.s + 0].x;
		ex.yd = ex.vert[ex.s + 1].y - ex.vert[ex.s + 0].y;
		ex.dx = ex.xd * (ex.dx * ex.xd + ex.yd * ex.dy) /
			(ex.xd * ex.xd + ex.yd * ex.yd);
		ex.dy = ex.yd * (ex.dx * ex.xd + ex.yd * ex.dy) /
			(ex.xd * ex.xd + ex.yd * ex.yd);
		mlx->moving = 0;
	}
}

static void	game_moving(t_mlx *mlx, t_expose ex)
{
	ex.px = mlx->player.where.x;
	ex.py = mlx->player.where.y;
	ex.dx = mlx->player.velocity.x;
	ex.dy = mlx->player.velocity.y;
	ex.sect = &mlx->sectors[mlx->player.sector];
	ex.vert = ex.sect->vertex;
	while (++ex.s < ex.sect->npoints)
	{
		if (intersect_box(new_pos(ex.px, ex.py),
					new_pos(ex.px + ex.dx, ex.py + ex.dy),
					new_pos(ex.vert[ex.s + 0].x, ex.vert[ex.s + 0].y),
					new_pos(ex.vert[ex.s + 1].x, ex.vert[ex.s + 1].y))
				&& point_side(new_pos(ex.px + ex.dx, ex.py + ex.dy),
					new_pos(ex.vert[ex.s + 0].x, ex.vert[ex.s + 0].y),
					new_pos(ex.vert[ex.s + 1].x, ex.vert[ex.s + 1].y)) < 0)
			game_moving2(mlx, ex);
	}
	move_player(mlx, ex.dx, ex.dy);
	mlx->falling = 1;
}

static void	mv_player(t_mlx *mlx, t_expose *ex)
{
	if (mlx->wasd[0])
	{
		ex->move_vec[0] += mlx->player.anglecos * SPEED;
		ex->move_vec[1] += mlx->player.anglesin * SPEED;
	}
	if (mlx->wasd[1])
	{
		ex->move_vec[0] += mlx->player.anglesin * SPEED;
		ex->move_vec[1] -= mlx->player.anglecos * SPEED;
	}
	if (mlx->wasd[2])
	{
		ex->move_vec[0] -= mlx->player.anglecos * SPEED;
		ex->move_vec[1] -= mlx->player.anglesin * SPEED;
	}
	if (mlx->wasd[3])
	{
		ex->move_vec[0] -= mlx->player.anglesin * SPEED;
		ex->move_vec[1] += mlx->player.anglecos * SPEED;
	}
	ex->pushing = mlx->wasd[0] || mlx->wasd[1] || mlx->wasd[2] || mlx->wasd[3];
	ex->acceleration = ex->pushing ? 0.4 : 0.2;
}

void		game(t_mlx *mlx, t_expose ex)
{
	if (mlx->falling)
		game_falling(mlx, ex);
	if (mlx->moving)
		game_moving(mlx, ex);
	mlx->player.angle += mlx->mouse.x * 0.01f;
	ex.yaw = clamp(ex.yaw + mlx->mouse.y * 0.01f, -5, 5);
	mlx->player.yaw = ex.yaw - mlx->player.velocity.z * 0.5f;
	move_player(mlx, 0, 0);
	ex.move_vec[0] = 0.f;
	ex.move_vec[1] = 0.f;
	mv_player(mlx, &ex);
	mlx->player.velocity.x = mlx->player.velocity.x
		* (1 - ex.acceleration) + ex.move_vec[0] * ex.acceleration;
	mlx->player.velocity.y = mlx->player.velocity.y
		* (1 - ex.acceleration) + ex.move_vec[1] * ex.acceleration;
	if (ex.pushing)
		mlx->moving = 1;
	gameplay(mlx);
}
