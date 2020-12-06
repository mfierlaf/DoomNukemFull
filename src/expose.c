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
	else if (mlx->editor.on)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		clear_img(mlx->editor.data_map, mlx->editor.map_img_width, H);
		clear_img(mlx->editor.data_buttons, mlx->editor.buttons_img_width, H);
		map_editor(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->editor.img_map, 0, 0);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->editor.img_buttons, mlx->editor.map_img_width, 0);
	}
	else
	{
		ex.s = -1;
		ex.yaw = 0;
		mlx->player.angle = 0;
		clear_img(mlx->data, W, H);
		ex.eyeheight = mlx->ducking ? DUCKHEIGHT : EYEHEIGHT;
		mlx->ground = !mlx->falling;
		game(mlx, ex);
	}
	return (0);
}
