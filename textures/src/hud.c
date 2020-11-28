/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <cvan-duf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:53:03 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/10/09 16:34:15 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void			draw_ammo(t_mlx *mlx)
{
	int		i;
	int		gap;
	t_point	size;

	i = 1;
	gap = 10;
	size.x = 3;
	size.y = 15;
	while (i <= mlx->inventory.ammo)
	{
		filled_rect(size, i + W / 1.01 - gap * i, H / 76.8, mlx);
		i++;
	}
}

void			draw_shield(t_mlx *mlx)
{
	int		i;
	int		gap;
	t_point	coord;

	i = 1;
	gap = 3;
	while (i <= mlx->inventory.shield)
	{
		coord.x = i + W / 4 + gap * i;
		coord.y = H / 1.15;
		draw_image(coord, 1, mlx->tab_bmp[SHIELD], mlx);
		i += 10;
	}
}

void			draw_life_bar(t_mlx *mlx)
{
	t_point	size;
	t_point	filled_size;

	filled_size.x = mlx->player.life * W / 440;
	filled_size.y = W / 32.6;
	filled_rect(filled_size, W / 128, H / 1.1, mlx);
	size.x = W / 4.4;
	size.y = W / 32.6;
	draw_rect(size, W / 128, H / 1.1, mlx);
}

void			draw_weapon_hud(t_mlx *mlx)
{
	t_point coord;

	coord.x = W / 1.15;
	if (mlx->inventory.weapon_type[3])
	{
		coord.y = H / -15.3;
		draw_image(coord, 2, mlx->tab_bmp[KNIFE], mlx);
	}
	if (mlx->inventory.weapon_type[2])
	{
		coord.y = H / 25.6;
		draw_image(coord, 2, mlx->tab_bmp[HAND_GUN], mlx);
	}
	if (mlx->inventory.weapon_type[0])
	{
		coord.x = W / 1.15;
		coord.y = H / 6.9;
		draw_image(coord, 2, mlx->tab_bmp[GUN], mlx);
	}
	if (mlx->inventory.weapon_type[1])
	{
		coord.x = W / 1.12;
		coord.y = H / 3.5;
		draw_image(coord, 1.5, mlx->tab_bmp[BIG_GUN], mlx);
	}
}

void			draw_hud(t_mlx *mlx)
{
	t_point	coord;
	t_point size;
	char* key_num;

	draw_weapon_hud(mlx);
	coord.x = W / 1.158;
	coord.y = H / 1.25;
	draw_image(coord, 2, mlx->tab_bmp[BLUE_KEY], mlx);
	key_num = ft_itoa(mlx->inventory.keys);
	mlx_string_put(mlx->mlx, mlx->win, W / 2, H / 2, 0x3D90B4, "key_num");
	draw_ammo(mlx);
	draw_life_bar(mlx);
	if (mlx->inventory.shield)
		draw_shield(mlx);
	size.x = W / 6.14;
	size.y = H / 12.36;
	if (mlx->weapon.anim >= 15)
		draw_rect(size, W / 1.20, H / 25, mlx);
	else if (mlx->weapon.anim >= 10 && mlx->weapon.anim <= 14)
		draw_rect(size, W / 1.20, H / 7, mlx);
	else if (mlx->weapon.anim >= 0 && mlx->weapon.anim <= 4)
		draw_rect(size, W / 1.20, H / 4.2, mlx);
	else
		draw_rect(size, W / 1.20, H / 3, mlx);
}
