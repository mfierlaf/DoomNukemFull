/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fverhuls <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 16:28:52 by fverhuls          #+#    #+#             */
/*   Updated: 2020/02/24 14:00:03 by fverhuls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void		enter_menu(t_mlx *mlx)
{
	if (mlx->menu.gun_pointer == 0)
	{
		mlx->menu.on = 0;
		// if (mlx->player->is_dead > 0)
		// {
		// 	init(mlx);
		// 	mlx->menu.on = 0;
		// }
	}
	// if (mlx->menu.gun_pointer == 1)
	// {
	// 	mlx->editor->on = 1;
	// 	mlx->menu.on = 0;
	// }
	if (mlx->menu.gun_pointer == 2)
	{
		mlx->music.mute = !mlx->music.mute;
		music(mlx);
	}
	else if (mlx->menu.gun_pointer == 5)
		kill_mlx(mlx);
}

void		music_menu(int key, t_mlx *mlx)
{
	if (key == LEFT_KEY && mlx->music.music > 0)
	{
		mlx->music.music -= 1;
		system("pkill afplay");
		music(mlx);
	}
	else if (key == RIGHT_KEY && mlx->music.music <= 2)
	{
		mlx->music.music += 1;
		system("pkill afplay");
		music(mlx);
	}
}

// void		switch_wepon(int key, t_mlx *mlx)
// {
// 	if (key == K1_KEY)
// 		mlx->weapon.anim = 15;
// 	if (key == K2_KEY && mlx->inventory.weapon_type[2])
// 		mlx->weapon.anim = 10;
// 	if (key == K3_KEY && mlx->inventory.weapon_type[0])
// 		mlx->weapon.anim = 0;
// 	if (key == K4_KEY && mlx->inventory.weapon_type[1])
// 		mlx->weapon.anim = 5;
// }

void		menu_key_hook(int key, t_mlx *mlx)
{
	if (mlx->menu.on)
	{
		if (key == DOWN_KEY && mlx->menu.gun_pointer < 5)
			mlx->menu.gun_pointer += 1;
		else if (key == UP_KEY && mlx->menu.gun_pointer > 0)
			mlx->menu.gun_pointer -= 1;
		if (mlx->menu.gun_pointer == 3)
			music_menu(key, mlx);
		if (mlx->menu.gun_pointer == 4)
		{
			if (key == LEFT_KEY && mlx->menu.bot_level < 20000)
				mlx->menu.bot_level += 6000;
			else if (key == RIGHT_KEY && mlx->menu.bot_level >= 6000)
				mlx->menu.bot_level -= 6000;
		}
		if (key == RTN_KEY)
			enter_menu(mlx);
		if (!mlx->music.mute && (key == DOWN_KEY || key == UP_KEY))
			system("afplay ./music/beep.mp3 &");
		menu(mlx);
	}
	// switch_wepon(key, mlx);
}
