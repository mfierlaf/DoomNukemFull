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
	// mlx->objects[0].order = 0;
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

void				shoot(t_mlx *mlx)
{
	int				sprite;
	t_pos			inter;
	t_pos			pl_pos;
	t_line			straight_ray;
	t_line			small_ray;
	t_pos			dir;
	float			off_angle;
	float			angle;
	float			slice;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	slice = M_PI / (3.0 * (float)W);
	angle = atan2(mlx->player.anglesin, mlx->player.anglecos);
	off_angle = ((W * 0.5)) * slice;
	dir.x = pl_pos.x + cos(off_angle + angle) * 50;
	dir.y = pl_pos.y + sin(off_angle + angle) * 50;
	straight_ray = new_line(pl_pos, dir);
	printf("dirx: %f\n", dir.x);
	printf("diry: %f\n", dir.y);

	dir.x = pl_pos.x + cos(off_angle + angle) * 10;
	dir.y = pl_pos.y + sin(off_angle + angle) * 10;
	small_ray = new_line(pl_pos, dir);
	sprite = 0;
	if (mlx->inventory.ammo || mlx->weapon.anim == 15)
	{
		if (mlx->weapon.anim < 15)
		{
			// bullet_deco(straight_ray, mlx);
			if (!mlx->music.mute)
				system("afplay ./music/gun.mp3 &");
		}
		else if (mlx->weapon.anim <= 15 && !mlx->music.mute)
			system("afplay ./music/stab.mp3 &");
		while (sprite < NB_OBJ)
		{
			if (mlx->weapon.anim >= 15)
				inter = get_intersection(straight_ray, mlx->objects[mlx->objects[sprite].order].sprite_line, get_slope(straight_ray), get_slope(mlx->objects[mlx->objects[sprite].order].sprite_line));
			else
				inter = get_intersection(small_ray, mlx->objects[mlx->objects[sprite].order].sprite_line, get_slope(small_ray), get_slope(mlx->objects[mlx->objects[sprite].order].sprite_line));
			if (!isnan(inter.x) && mlx->objects[mlx->objects[sprite].order].life > 0) //isinf?
			{
				mlx->objects[mlx->objects[sprite].order].life -= mlx->weapon.damage;
				if (mlx->objects[mlx->objects[sprite].order].life <= 0)
				{
					mlx->objects[mlx->objects[sprite].order].initial_tex = mlx->objects[mlx->objects[sprite].order].initial_tex + mlx->objects[mlx->objects[sprite].order].nb_anim_walk;
					mlx->objects[mlx->objects[sprite].order].isbot = 2;
				}
				if (!mlx->music.mute)
					system("afplay ./music/death.mp3 &");
			}
			sprite++;
		}
	}
}
