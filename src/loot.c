/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jreynaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:51 by jreynaer          #+#    #+#             */
/*   Updated: 2019/10/10 13:07:38 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void			loot_power2(int sprite, t_mlx *mlx)
{
	if (mlx->objects[mlx->objects[sprite].order].tex == BIG_GUN)
	{
		mlx->inventory.weapon_type[1] = 1;
		mlx->weapon.anim = 5;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == GUN)
	{
		mlx->inventory.weapon_type[0] = 1;
		mlx->weapon.anim = 0;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == HAND_GUN)
	{
		mlx->inventory.weapon_type[2] = 1;
		mlx->weapon.anim = 10;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == AMMO)
		mlx->inventory.ammo += 10;
	else if (mlx->objects[mlx->objects[sprite].order].tex == SHIELD)
		mlx->inventory.shield += 10;
	else if (mlx->objects[mlx->objects[sprite].order].tex == CHALICE)
		mlx->inventory.grail++;
}

static void			loot_power(int sprite, t_mlx *mlx)
{
	if (mlx->objects[mlx->objects[sprite].order].tex == CHICKEN_LEG)
	{
		if (mlx->player.life + 50 < 100)
			mlx->player.life += 50;
		else
			mlx->player.life = 100;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == MED_KIT)
	{
		if (mlx->player.life + 70 < 100)
			mlx->player.life += 70;
		else
			mlx->player.life = 100;
	}
	else if (mlx->objects[mlx->objects[sprite].order].tex == BLUE_KEY || mlx->objects
			[mlx->objects[sprite].order].tex == GOLDEN_KEY)
		mlx->inventory.keys++;
	loot_power2(sprite, mlx);
}

void				pick_up_loot(t_mlx *mlx)
{
	int			sprite;

	sprite = 0;
	while (sprite < NB_OBJ)
	{
		if (((int)mlx->player.where.x == (int)mlx->objects[mlx->objects[sprite].order].pos.x 
			&& (int)mlx->player.where.y == (int)mlx->objects[mlx->objects[sprite].order].pos.y) &&
				mlx->objects[mlx->objects[sprite].order].lootable)
		{
			loot_power(sprite, mlx);
			mlx->objects[mlx->objects[sprite].order].tex = -1;
		}
		sprite++;
	}
}
