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

// void				shoot_direction(t_mlx *mlx)
// {
// 	float		slice;
// 	float		angle;
// 	float		off_angle;

// 	slice = M_PI / (3.0 * (float)W);
// 	angle = atan2(mlx->player.dir.y, mlx->player.dir.x);
// 	off_angle = (W / 2 - ((float)W * 0.5)) * slice;
// 	angle += off_angle;
// 	mlx->weapon.dir_shoot.x = mlx->player.where.x + cos(angle) * DEPTH;
// 	mlx->weapon.dir_shoot.y = mlx->player.where.y + sin(angle) * DEPTH;
// 	mlx->objects[0].pos.x = mlx->player.where.x;
// 	mlx->objects[0].pos.y = mlx->player.where.y;
// }

// void				send_bullet(t_mlx *mlx)
// {
// 	int			sector;
// 	float		dist;

// 	if (mlx->anim.shoot)
// 	{
// 		sector = find_sector(mlx, mlx->player.where);
// 		mlx->objects[0].tex = 89;
// 		mlx->objects[0].pos.x += (mlx->weapon.dir_shoot.x - mlx->objects
// 			[0].pos.x) * 0.02;
// 		mlx->objects[0].pos.y += (mlx->weapon.dir_shoot.y - mlx->objects
// 			[0].pos.y) * 0.02;
// 		dist = get_dist(mlx->objects[0].pos, mlx->player.where);
// 		if (dist > 5)
// 		{
// 			mlx->objects[0].pos.x = mlx->player.where.x;
// 			mlx->objects[0].pos.y = mlx->player.where.y;
// 			mlx->anim.shoot = 0;
// 			mlx->objects[0].tex = -1;
// 		}
// 	}
// }

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

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	sprite = 0;
	if (mlx->inventory.ammo || mlx->weapon.anim == 15)
	{
		if (mlx->weapon.anim < 15)
		{
			// bullet_deco(mlx->ray, mlx);
			if (!mlx->music.mute)
				system("afplay ./music/gun.mp3 &");
		}
		else if (mlx->weapon.anim <= 15 && !mlx->music.mute)
			system("afplay ./music/stab.mp3 &");
		while (sprite < NB_OBJ)
		{
			if (mlx->weapon.anim >= 15)
				inter = get_intersection(mlx->ray, mlx->objects[sprite].sprite_line, get_slope(mlx->ray), get_slope(mlx->objects[sprite].sprite_line));
			else
				inter = get_intersection(new_line(pl_pos, pl_pos), mlx->objects[sprite].sprite_line, get_slope(new_line(pl_pos, pl_pos)), get_slope(mlx->objects[sprite].sprite_line));
			if (!isnan(inter.x) && mlx->objects[sprite].life > 0) //isinf?
			{
				mlx->objects[sprite].life -= mlx->weapon.damage;
				if (mlx->objects[sprite].life <= 0)
				{
					printf("tex: %d\n", mlx->objects[sprite].initial_tex);
					printf("tex: %d\n", mlx->objects[sprite].nb_anim_walk);
					mlx->objects[sprite].initial_tex = mlx->objects[sprite].initial_tex + mlx->objects[sprite].nb_anim_walk;
					printf("tex: %d\n", mlx->objects[sprite].initial_tex);
					mlx->objects[sprite].isbot = 2;
				}
				if (!mlx->music.mute)
					system("afplay ./music/death.mp3 &");
			}
			sprite++;
		}
	}
}
