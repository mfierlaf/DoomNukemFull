/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	gameplay(t_mlx *mlx)
{
	if (mlx->player.life <= 0)
	{
		mlx->player.is_dead = 1;
		mlx->menu.on = 1;
	}
	else if (mlx->inventory.grail)
	{
		mlx->player.is_dead = 2;
		mlx->menu.on = 1;
	}
	draw_screen(mlx);
	draw_hud(mlx);
	send_bullet(mlx);
	weapon_choice(mlx);
	shoot_anim(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	if (mlx->inventory.count < 300)
		mlx->inventory.count++;
	story(mlx);
}

int		expose(t_mlx *mlx)
{
	t_expose	ex;

	if (mlx->menu.on)
	{
		menu(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		menu_strings(mlx);
	}
	else
	{
		ex.s = -1;
		ex.yaw = 0;
		mlx->player.angle = 0;
		clear_img(mlx);
		ex.eyeheight = mlx->ducking ? DUCKHEIGHT : EYEHEIGHT;
		mlx->ground = !mlx->falling;
		game(mlx, ex);
	}
	return (0);
}
