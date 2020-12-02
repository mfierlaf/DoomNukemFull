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
	mlx->menu.bot_level = 20000;
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
	mlx->weapon.anim = KNIFE_ANIM_0;
	mlx->weapon.damage = 50;
	mlx->player.life = 100;
	mlx->player.is_dead = 0;
	mlx->anim.curr_anim = 0;
	mlx->editor.on = 0;
	mlx->editor.map_img_width = ((3 * W) / 4);
	mlx->editor.buttons_img_width = (W / 4);
	mlx->editor.start.x = -1;
	mlx->editor.start.y = -1;
	mlx->editor.end.x = -1;
	mlx->editor.end.x = -1;
	mlx->editor.off_x = mlx->editor.map_img_width - 10;
	mlx->editor.off_y = H - 10;
	mlx->editor.old_x = 0;
	mlx->editor.old_y = 0;
	mlx->editor.sqr_size = 60;
	mlx->editor.button_toggled = 0;
	mlx->events.but1 = 0;
	mlx->events.new_sector = 0;
	init_buttons(mlx);
}
