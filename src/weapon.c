/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jreynaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:51 by jreynaer          #+#    #+#             */
/*   Updated: 2019/10/10 13:07:38 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void				shoot_direction(t_mlx *mlx)
{
	float		slice;
	float		angle;
	float		off_angle;

	slice = M_PI / (3.0 * (float)W);
	angle = atan2(mlx->player.anglesin, mlx->player.anglecos);
	off_angle = (W / 2 - ((float)W * 0.5)) * slice;
	angle += off_angle;
	mlx->weapon.dir_shoot.x = mlx->player.where.x + cos(angle) * 50;
	mlx->weapon.dir_shoot.y = mlx->player.where.y + sin(angle) * 50;
	mlx->objects[0].pos.x = mlx->player.where.x;
	mlx->objects[0].pos.y = mlx->player.where.y;
	mlx->objects[0].tex = -1;
	mlx->objects[0].sector = 0;
}

void				send_bullet(t_mlx *mlx)
{
	float		dist;
	t_pos		pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	if (mlx->anim.shoot)
	{
		mlx->objects[0].tex = BULLET;
		mlx->objects[0].pos.x += (mlx->weapon.dir_shoot.x - mlx->objects
			[0].pos.x) * 0.02;
		mlx->objects[0].pos.y += (mlx->weapon.dir_shoot.y - mlx->objects
			[0].pos.y) * 0.02;
		mlx->objects[0].sector = mlx->player.sector;
		dist = get_dist(mlx->objects[0].pos, pl_pos);
		if (dist > 5)
		{
			mlx->objects[0].pos.x = mlx->player.where.x;
			mlx->objects[0].pos.y = mlx->player.where.y;
			mlx->anim.shoot = 0;
			mlx->objects[0].tex = -1;
		}
	}
}

void				weapon_choice(t_mlx *mlx)
{
	if (mlx->weapon.anim >= 15)
		mlx->weapon.damage = 100;
	else if (mlx->weapon.anim >= 10 && mlx->weapon.anim <= 14)
		mlx->weapon.damage = 50;
	else if (mlx->weapon.anim >= 0 && mlx->weapon.anim <= 4)
		mlx->weapon.damage = 100;
	else
		mlx->weapon.damage = 70;
}

static void			shoot_calc(t_shoot *shoot, t_mlx *mlx)
{
	shoot->pl_pos.x = mlx->player.where.x;
	shoot->pl_pos.y = mlx->player.where.y;
	shoot->slice = M_PI / (3.0 * (float)W);
	shoot->angle = atan2(mlx->player.anglesin, mlx->player.anglecos);
	shoot->off_angle = ((W * 0.5)) * shoot->slice;
	shoot->dir.x = shoot->pl_pos.x + cos(shoot->off_angle + shoot->angle) * 50;
	shoot->dir.y = shoot->pl_pos.y + sin(shoot->off_angle + shoot->angle) * 50;
	shoot->straight_ray = new_line(shoot->pl_pos, shoot->dir);
	shoot->dir.x = shoot->pl_pos.x + cos(shoot->off_angle + shoot->angle) * 10;
	shoot->dir.y = shoot->pl_pos.y + sin(shoot->off_angle + shoot->angle) * 10;
	shoot->small_ray = new_line(shoot->pl_pos, shoot->dir);
	shoot->sprite = 0;
}

void				shoot(t_mlx *mlx)
{
	t_shoot		shoot;

	shoot_calc(&shoot, mlx);
	if (mlx->inventory.ammo || mlx->weapon.anim == 15)
	{
		if (mlx->weapon.anim < 15)
		{
			if (!mlx->music.mute)
				system("afplay ./music/gun.mp3 &");
		}
		else if (mlx->weapon.anim <= 15 && !mlx->music.mute)
			system("afplay ./music/stab.mp3 &");
		while (shoot.sprite < NB_OBJ)
		{
			shoot_while(&shoot, mlx);
			shoot.sprite++;
		}
	}
}
