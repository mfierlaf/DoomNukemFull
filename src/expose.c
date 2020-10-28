/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                            :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:58:48 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/26 17:39:40 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

int expose(t_mlx *mlx)
{
	mlx->player.angle = 0;
	clear_img(mlx);
	float yaw = 0;

	/* Vertical collision detection */
	float eyeheight = mlx->ducking ? DuckHeight : EyeHeight;
	mlx->ground = !mlx->falling;
	if (mlx->falling)
	{
		mlx->player.velocity.z -= JUMP_SPEED; /* Add gravity */
		float nextz = mlx->player.where.z + mlx->player.velocity.z;
		if (mlx->player.velocity.z < 0 && nextz  < mlx->sectors[mlx->player.sector].floor + eyeheight) // When going down
		{
			/* Fix to ground */
			mlx->player.where.z = mlx->sectors[mlx->player.sector].floor + eyeheight;
			mlx->player.velocity.z = 0;
			mlx->falling = 0;
			mlx->ground  = 1;
		}
		else if (mlx->player.velocity.z > 0 && nextz > mlx->sectors[mlx->player.sector].ceil) // When going up
		{
			/* Prevent jumping above ceiling */
			mlx->player.velocity.z = 0;
			mlx->falling = 1;
		}
		if (mlx->falling)
		{
			mlx->player.where.z += mlx->player.velocity.z;
			mlx->moving = 1;
		}
	}
	/* Horizontal collision detection */
	if (mlx->moving)
	{
		float px = mlx->player.where.x,    py = mlx->player.where.y;
		float dx = mlx->player.velocity.x, dy = mlx->player.velocity.y;

		t_sector* sect = &mlx->sectors[mlx->player.sector];
		const struct xy* const vert = sect->vertex;
		/* Check if the player is about to cross one of the sector's edges */
		for (unsigned s = 0; s < sect->npoints; ++s)
			if (intersect_box(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
					&& point_side(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
			{
				/* Check where the hole is. */
				float hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, mlx->sectors[sect->neighbors[s]].floor);
				float hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil, mlx->sectors[sect->neighbors[s]].ceil );
				/* Check whether we're bumping into a wall. */
				if (hole_high < mlx->player.where.z+HeadMargin
						|| hole_low  > mlx->player.where.z-eyeheight+KneeHeight)
				{
					/* Bumps into a wall! Slide along the wall. */
					/* This formula is from Wikipedia article "vector projection". */
					float xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
					dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
					dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
					mlx->moving = 0;
				}
			}
		move_player(mlx, dx, dy);
		mlx->falling = 1;
	}

	/* mouse aiming */
	mlx->player.angle += mlx->mouse.x * 0.01f;
	yaw          = clamp(yaw + mlx->mouse.y * 0.01f, -5, 5);
	mlx->player.yaw   = yaw - mlx->player.velocity.z * 0.5f;
	move_player(mlx, 0, 0);

	float move_vec[2] = {0.f, 0.f};
	if (mlx->wasd[0])
	{
		move_vec[0] += mlx->player.anglecos * SPEED;
		move_vec[1] += mlx->player.anglesin * SPEED;
	}
	if (mlx->wasd[1])
	{
		move_vec[0] += mlx->player.anglesin * SPEED;
		move_vec[1] -= mlx->player.anglecos * SPEED;
	}
	if (mlx->wasd[2])
	{
		move_vec[0] -= mlx->player.anglecos * SPEED;
		move_vec[1] -= mlx->player.anglesin * SPEED;
	}
	if (mlx->wasd[3])
	{
		move_vec[0] -= mlx->player.anglesin * SPEED;
		move_vec[1] += mlx->player.anglecos * SPEED;
	}

	int pushing = mlx->wasd[0] || mlx->wasd[1] || mlx->wasd[2] || mlx->wasd[3];
	float acceleration = pushing ? 0.4 : 0.2;

	mlx->player.velocity.x = mlx->player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
	mlx->player.velocity.y = mlx->player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

	if (pushing)
		mlx->moving = 1;

	draw_screen(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}
