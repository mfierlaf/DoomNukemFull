/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:14:25 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 14:14:27 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void		menu_gun2(t_mlx *mlx)
{
	t_point coord;

	coord.x = W / 10;
	if (mlx->menu.gun_pointer == 3)
	{
		coord.y = H / 4;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
	else if (mlx->menu.gun_pointer == 4)
	{
		coord.y = H / 3.2;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
	else if (mlx->menu.gun_pointer == 5)
	{
		coord.y = H / 2.6;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
}

void		menu_gun(t_mlx *mlx)
{
	t_point coord;

	coord.x = W / 10;
	if (mlx->menu.gun_pointer <= 0)
	{
		coord.y = H / 11;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
	else if (mlx->menu.gun_pointer == 1)
	{
		coord.y = H / 6.5;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
	else if (mlx->menu.gun_pointer == 2)
	{
		coord.y = H / 5;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
	menu_gun2(mlx);
}

void		menu(t_mlx *mlx)
{
	t_point coord;

	coord.x = 0;
	coord.y = -160;
	draw_image(coord, 0.55, mlx->tab_bmp[BACKGROUND], mlx);
	menu_gun(mlx);
	if (mlx->music.mute == 1)
	{
		coord.x = W / 25.6;
		coord.y = H / 1.2;
		draw_image(coord, 0.5, mlx->tab_bmp[MUTE], mlx);
	}
}

void		story(t_mlx *mlx)
{
	char *keys;

	keys = ft_itoa(mlx->inventory.keys);
	mlx_string_put(mlx->mlx, mlx->win, W / 1.16, H / 1.075, 0x3D90B4, keys);
	free(keys);
	if (mlx->inventory.count < 300)
	{
		mlx_string_put(mlx->mlx, mlx->win, W / 128, H
			/ 1.5, 0x3D90B4, "Hello and welcome to planet Doom.");
		mlx_string_put(mlx->mlx, mlx->win, W / 128, H
			/ 1.4, 0x3D90B4, "You have been in a crash with your vessel");
		mlx_string_put(mlx->mlx, mlx->win, W / 128, H
			/ 1.32, 0x3D90B4, "on this \
			planet ruled by futuristic nazis.");
		mlx_string_put(mlx->mlx, mlx->win, W / 128, H
			/ 1.25, 0x3D90B4, "Find the grail and you will be free.");
	}
}
