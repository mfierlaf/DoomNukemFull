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
	if (mlx->objects[mlx->objects[sprite].order].tex == PRIEST_1)
	{
		mlx->objects[mlx->objects[sprite].order].nb_anim = 7;
		mlx->objects[mlx->objects[sprite].order].nb_anim_walk = 4;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == MECH_1)
	{
		mlx->objects[mlx->objects[sprite].order].nb_anim = 4;
		mlx->objects[mlx->objects[sprite].order].nb_anim_walk = 7;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == NORMAL_1)
	{
		mlx->objects[mlx->objects[sprite].order].nb_anim = 8;
		mlx->objects[mlx->objects[sprite].order].nb_anim_walk = 7;
	}
	else
	{
		mlx->objects[mlx->objects[sprite].order].nb_anim = 1;
		mlx->objects[mlx->objects[sprite].order].nb_anim_walk = 1;
	}
}

void		sprite_var(int sprite, t_mlx *mlx)
{
	if (mlx->objects[mlx->objects[sprite].order].tex == CHICKEN_LEG ||
			mlx->objects[mlx->objects[sprite].order].tex == MED_KIT ||
			mlx->objects[mlx->objects[sprite].order].tex == BIG_GUN ||
			mlx->objects[mlx->objects[sprite].order].tex == GUN ||
			mlx->objects[mlx->objects[sprite].order].tex == HAND_GUN ||
			mlx->objects[mlx->objects[sprite].order].tex == AMMO ||
			mlx->objects[mlx->objects[sprite].order].tex == SHIELD ||
			mlx->objects[mlx->objects[sprite].order].tex == BLUE_KEY ||
			mlx->objects[mlx->objects[sprite].order].tex == GOLDEN_KEY ||
			mlx->objects[mlx->objects[sprite].order].tex == CHALICE)
		mlx->objects[mlx->objects[sprite].order].lootable = 1;
	else
		mlx->objects[mlx->objects[sprite].order].lootable = 0;
	if (mlx->objects[mlx->objects[sprite].order].life > 0)
		mlx->objects[mlx->objects[sprite].order].isbot = 1;
	else
		mlx->objects[mlx->objects[sprite].order].isbot = 0;
	mlx->objects[mlx->objects[sprite].order].initial_tex =
		mlx->objects[mlx->objects[sprite].order].tex;
	enemy_anim_num(sprite, mlx);
}

static void	init_shot(t_mlx *mlx)
{
	mlx->objects[0].tex = -1;
	mlx->objects[0].sector = 0;
	mlx->objects[0].lootable = 0;
	mlx->objects[0].pos.x = 0;
	mlx->objects[0].pos.y = 0;
	mlx->objects[0].order = 0;
	mlx->objects[0].distance = 0;
	mlx->objects[0].life = 0;
	mlx->objects[0].isbot = 0;
	mlx->objects[0].initial_tex = 0;
	mlx->objects[0].nb_anim_walk = 0;
	mlx->objects[0].nb_anim = 0;
}

static void	init_menu(t_mlx *mlx)
{
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
}

void		init(t_mlx *mlx)
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
	mlx->player.life = 100;
	mlx->player.is_dead = 0;
	mlx->editor.on = 0;
	mlx->editor.map_img_width = ((3 * W) / 4);
	mlx->player.dir.x = 1.0;
	mlx->player.dir.y = 0.0;
	mlx->sleep.death = 0;
	mlx->sleep.walk = 0;
	mlx->sleep.shoot = 0;
	mlx->anim.curr_anim_walk = 0;
	mlx->anim.curr_anim = 0;
	mlx->flying = 0;
	init_menu(mlx);
	init_shot(mlx);
}
