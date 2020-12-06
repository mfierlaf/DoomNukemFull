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
		if (mlx->player.is_dead > 0)
		{
			unload_data(mlx);
			init(mlx);
			load_data(mlx);
			mlx->menu.on = 0;
		}
	}
	if (mlx->menu.gun_pointer == 1)
	{
		mlx->editor.on = 1;
		mlx->menu.on = 0;
	}
	if (mlx->menu.gun_pointer == 2)
	{
		mlx->music.mute = !mlx->music.mute;
		music(mlx);
	}
	else if (mlx->menu.gun_pointer == 5)
		kill_mlx("", mlx);
}

void		music_menu(int key, t_mlx *mlx)
{
	if ((key == LEFT_KEY || key == LEFT_ARROW) && mlx->music.music > 0)
	{
		mlx->music.music -= 1;
		system("pkill afplay");
		music(mlx);
	}
	else if ((key == RIGHT_KEY || key == RIGHT_ARROW) && mlx->music.music <= 2)
	{
		mlx->music.music += 1;
		system("pkill afplay");
		music(mlx);
	}
}

void		switch_weapon(int key, t_mlx *mlx)
{
	if (key == K1_KEY || key == K1_LN)
		mlx->weapon.anim = 15;
	if ((key == K2_KEY || key == K2_LN) && mlx->inventory.weapon_type[2])
		mlx->weapon.anim = 10;
	if ((key == K3_KEY || key == K3_LN) && mlx->inventory.weapon_type[0])
		mlx->weapon.anim = 0;
	if ((key == K4_KEY || key == K4_LN) && mlx->inventory.weapon_type[1])
		mlx->weapon.anim = 5;
}

void		menu_key_hook(int k, t_mlx *mlx)
{
	if (mlx->menu.on)
	{
		if ((k == DOWN_KEY || k == DOWN_ARROW) && mlx->menu.gun_pointer < 5)
			mlx->menu.gun_pointer += 1;
		else if ((k == UP_KEY || k == UP_ARROW) && mlx->menu.gun_pointer > 0)
			mlx->menu.gun_pointer -= 1;
		if (mlx->menu.gun_pointer == 3)
			music_menu(k, mlx);
		if (mlx->menu.gun_pointer == 4)
		{
			if ((k == LEFT_KEY || k == LEFT_ARROW) &&
			mlx->menu.bot_level < 38000)
				mlx->menu.bot_level += 10000;
			else if ((k == RIGHT_KEY || k == RIGHT_ARROW) &&
			mlx->menu.bot_level >= 18000)
				mlx->menu.bot_level -= 10000;
		}
		if (k == RTN_KEY || k == ENTR_LN)
			enter_menu(mlx);
		if (!mlx->music.mute && (k == DOWN_KEY || k == UP_KEY
			|| k == DOWN_ARROW || k == UP_ARROW))
			system("afplay ./music/beep.mp3 &");
		menu(mlx);
	}
	switch_weapon(k, mlx);
}
