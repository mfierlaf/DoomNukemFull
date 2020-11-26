/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void		enemy_anim_num(int sprite, t_mlx *mlx)
{
	if (mlx->objects[sprite].tex == PRIEST_1)
	{
		mlx->objects[sprite].nb_anim = 7;
		mlx->objects[sprite].nb_anim_walk = 4;
	}
	else if (mlx->objects[sprite].tex == MECH_1)
	{
		mlx->objects[sprite].nb_anim = 4;
		mlx->objects[sprite].nb_anim_walk = 7;
	}
	else if (mlx->objects[sprite].tex == NORMAL_1)
	{
		mlx->objects[sprite].nb_anim = 8;
		mlx->objects[sprite].nb_anim_walk = 7;
	}
	else
	{
		mlx->objects[sprite].nb_anim = 1;
		mlx->objects[sprite].nb_anim_walk = 1;
	}
}

void		sprite_var(int sprite, t_mlx *mlx)
{
	if (mlx->objects[sprite].tex == CHICKEN_LEG ||
			mlx->objects[sprite].tex == MED_KIT ||
			mlx->objects[sprite].tex == BIG_GUN ||
			mlx->objects[sprite].tex == GUN ||
			mlx->objects[sprite].tex == HAND_GUN ||
			mlx->objects[sprite].tex == AMMO ||
			mlx->objects[sprite].tex == SHIELD ||
			mlx->objects[sprite].tex == BLUE_KEY ||
			mlx->objects[sprite].tex == GOLDEN_KEY ||
			mlx->objects[sprite].tex == CHALICE)
		mlx->objects[sprite].lootable = 1;
	else
		mlx->objects[sprite].lootable = 0;
	if (mlx->objects[sprite].life > 0)
		mlx->objects[sprite].isbot = 1;
	else
		mlx->objects[sprite].isbot = 0;
	mlx->objects[sprite].initial_tex = mlx->objects[sprite].tex;
	enemy_anim_num(sprite, mlx);
}

void	init(t_mlx *mlx)
{
	mlx->txty = 0;
	mlx->moving = 0;
	mlx->wasd[0] = 0;
	mlx->wasd[1] = 0;
	mlx->wasd[2] = 0;
	mlx->wasd[3] = 0;
	mlx->ground = 0;
	mlx->falling = 0;
	mlx->ducking = 0;
	mlx->sectors = NULL;
	mlx->num_sectors = 0;
	mlx->menu.on = 1;
	mlx->menu.gun_pointer = 0;
	mlx->menu.bot_level = 38000;
	mlx->music.music = 0;
	mlx->music.mute = 1;
	mlx->inventory.ammo = 10;
	mlx->inventory.shield = 10;
	mlx->inventory.keys = 0;
	mlx->inventory.weapon_type[0] = 1;
	mlx->inventory.weapon_type[1] = 1;
	mlx->inventory.weapon_type[2] = 1;
	mlx->inventory.weapon_type[3] = 1;
	mlx->inventory.count = 0;
	mlx->inventory.grail = 0;
	mlx->weapon.anim = KNIFE_ANIM_0;
	mlx->weapon.damage = 50;
	mlx->player.life = 100;
	mlx->player.is_dead = 0;
	mlx->anim.curr_anim = 0;
	mlx->editor.on = 0;
	mlx->editor.map_img_width = ((3 * W) / 4);
	mlx->player.dir.x = 1.0;
	mlx->player.dir.y = 0.0;
	mlx->sleep.death = 0;
	mlx->sleep.walk = 0;
	mlx->sleep.shoot = 0;
	mlx->anim.curr_anim_walk = 0;
	mlx->anim.curr_anim = 0;
}
