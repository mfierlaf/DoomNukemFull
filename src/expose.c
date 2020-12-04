/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

int		expose(t_mlx *mlx)
{
	float		eyeheight;
	float		nextz;
	float		px;
	float		py;
	float		dx;
	float		dy;
	struct xy	*vert;
	float		yaw;
	unsigned	s;
	float		hole_low;
	float		hole_high;
	float		xd;
	float		yd;
	float		move_vec[2];
	float		rot_speed;
	float		old_dir_x;
	int			pushing;
	float		acceleration;
	t_sector	*sect;

	if (mlx->menu.on)
	{
		menu(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		menu_strings(mlx);
	}
/*
**	else if (mlx->editor.on)
**	{
**		mlx_clear_window(mlx->mlx, mlx->win);
**		map_editor(mlx);
**		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->editor.img, 0, 0);
**	}
*/
	else
	{
		s = -1;
		yaw = 0;
		mlx->player.angle = 0;
		clear_img(mlx);
		eyeheight = mlx->ducking ? DuckHeight : EyeHeight;
		mlx->ground = !mlx->falling;
		if (mlx->falling)
		{
			if (!mlx->flying)
				mlx->player.velocity.z -= JUMP_SPEED;
			nextz = mlx->player.where.z + mlx->player.velocity.z;
			if (mlx->player.velocity.z < 0 && nextz
				< mlx->sectors[mlx->player.sector].floor + eyeheight)
			{
				mlx->player.where.z =
					mlx->sectors[mlx->player.sector].floor + eyeheight;
				mlx->player.velocity.z = 0;
				mlx->falling = 0;
				mlx->ground = 1;
			}
			else if (mlx->player.velocity.z >
				0 && nextz > mlx->sectors[mlx->player.sector].ceil)
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
		if (mlx->moving)
		{
			px = mlx->player.where.x;
			py = mlx->player.where.y;
			dx = mlx->player.velocity.x;
			dy = mlx->player.velocity.y;
			sect = &mlx->sectors[mlx->player.sector];
			vert = sect->vertex;
			while (++s < sect->npoints)
			{
				if (intersect_box(px, py, px + dx, py + dy, vert[s + 0].x,
					vert[s + 0].y, vert[s + 1].x, vert[s + 1].y)
						&& point_side(px + dx, py + dy, vert[s + 0].x,
							vert[s + 0].y, vert[s + 1].x, vert[s + 1].y) < 0)
				{
					hole_low = sect->neighbors[s] < 0 ? 9e9 :
					max(sect->floor, mlx->sectors[sect->neighbors[s]].floor);
					hole_high = sect->neighbors[s] < 0 ? -9e9 :
					min(sect->ceil, mlx->sectors[sect->neighbors[s]].ceil);
					if (hole_high < mlx->player.where.z + HeadMargin
						|| hole_low > mlx->player.where.z -
						eyeheight + KneeHeight)
					{
						xd = vert[s + 1].x - vert[s + 0].x;
						yd = vert[s + 1].y - vert[s + 0].y;
						dx = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						dy = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						mlx->moving = 0;
					}
				}
			}
			move_player(mlx, dx, dy);
			mlx->falling = 1;
		}
		mlx->player.angle += mlx->mouse.x * 0.01f;
		yaw = clamp(yaw + mlx->mouse.y * 0.01f, -5, 5);
		mlx->player.yaw = yaw - mlx->player.velocity.z * 0.5f;
		move_player(mlx, 0, 0);
		move_vec[0] = 0.f;
		move_vec[1] = 0.f;
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
		pushing = mlx->wasd[0] || mlx->wasd[1] || mlx->wasd[2] || mlx->wasd[3];
		acceleration = pushing ? 0.4 : 0.2;
		mlx->player.velocity.x = mlx->player.velocity.x
		* (1 - acceleration) + move_vec[0] * acceleration;
		mlx->player.velocity.y = mlx->player.velocity.y
		* (1 - acceleration) + move_vec[1] * acceleration;
		rot_speed = ((2 * M_PI) * (mlx->mouse.x - mlx->player.old_dir.x)) / W;
		old_dir_x = mlx->player.dir.x;
		mlx->player.dir.x = mlx->player.dir.x * cos(rot_speed) -
			mlx->player.dir.y * sin(rot_speed);
		mlx->player.dir.y = old_dir_x * sin(rot_speed) +
			mlx->player.dir.y * cos(rot_speed);
		if (pushing)
			mlx->moving = 1;
		if (mlx->player.life <= 0)
		{
			mlx->player.is_dead = 1;
			mlx->menu.on = 1;
		}
		else if (mlx->inventory.grail)
		{
			mlx->player.is_dead = 2;
			mlx->menu.on = 1;
		}
		draw_screen(mlx);
		draw_hud(mlx);
		send_bullet(mlx);
		weapon_choice(mlx);
		shoot_anim(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		if (mlx->inventory.count < 300)
			mlx->inventory.count++;
		story(mlx);
	}
	return (0);
}
