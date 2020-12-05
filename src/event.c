/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

/*
**	if (x < 0 || x > W || y < 0 || y > H)
**    mlx_mouse_move(mlx->win, W / 2, H / 2);
*/

int		mouse_hook(int x, int y, t_mlx *mlx)
{
	mlx->mouse.x = x;
	mlx->mouse.y = y;
	return (0);
}

void	mvt_hook(int key, t_mlx *mlx)
{
	if (key == UP_KEY || key == W_KEY || key == UP_ARROW || key == W_LN)
		mlx->wasd[0] = 1;
	if (key == LEFT_KEY || key == A_KEY || key == LEFT_ARROW || key == A_LN)
		mlx->wasd[1] = 1;
	if (key == DOWN_KEY || key == S_KEY || key == DOWN_ARROW || key == S_LN)
		mlx->wasd[2] = 1;
	if (key == RIGHT_KEY || key == D_KEY || key == RIGHT_ARROW || key == D_LN)
		mlx->wasd[3] = 1;
	if (key == SP_KEY || key == SP)
	{
		if (mlx->ground)
		{
			mlx->player.velocity.z += 0.5;
			mlx->falling = 1;
		}
		if (mlx->flying)
		{
			mlx->player.velocity.z += 0.5;
			mlx->falling = 1;
		}
	}
	if (key == F_KEY || key == F_LN)
		mlx->flying = !mlx->flying;
}

int		ft_key_hook(int key, t_mlx *mlx)
{
	if (key == ESC_KEY || key == ESC)
		kill_mlx("", mlx);
	mvt_hook(key, mlx);
	if (key == LCTRL_KEY || key == LCTRL)
	{
		if (mlx->flying)
			mlx->player.velocity.z -= 0.5;
		else
		{
			mlx->ducking = 1;
			mlx->moving = 1;
		}
	}
	if (key == M_KEY || key == M_LN)
		mlx->menu.on = !mlx->menu.on;
	if (key == E_KEY || key == E_LN)
		pick_up_loot(mlx);
	if (key == L_KEY || key == L_LN)
		mlx->sectors[mlx->player.sector].brightness =
			!mlx->sectors[mlx->player.sector].brightness;
	menu_key_hook(key, mlx);
	return (0);
}

int		button_mouse(int key, int x, int y, t_mlx *mlx)
{
	x += 0;
	y += 0;
	if (key == BUT1_KEY)
	{
		if (mlx->inventory.ammo || mlx->weapon.anim == 15)
		{
			if (mlx->weapon.anim < 15)
			{
				mlx->anim.shoot = 1;
				mlx->inventory.ammo--;
				shoot_direction(mlx);
			}
			shoot(mlx);
			mlx->anim.started = 1;
		}
		else if (mlx->weapon.anim < 15 && !mlx->music.mute)
			system("afplay ./music/click.mp3 &");
	}
	return (0);
}

int		stop_movement(int key, t_mlx *mlx)
{
	if (key == UP_KEY || key == W_KEY || key == UP_ARROW || key == W_LN)
		mlx->wasd[0] = 0;
	if (key == LEFT_KEY || key == A_KEY || key == LEFT_ARROW || key == A_LN)
		mlx->wasd[1] = 0;
	if (key == DOWN_KEY || key == S_KEY || key == DOWN_ARROW || key == S_LN)
		mlx->wasd[2] = 0;
	if (key == RIGHT_KEY || key == D_KEY || key == RIGHT_ARROW || key == D_LN)
		mlx->wasd[3] = 0;
	if (key == LCTRL_KEY || key == LCTRL)
	{
		if (mlx->flying)
			mlx->player.velocity.z = 0;
		else
		{
			mlx->ducking = 0;
			mlx->moving = 0;
		}
	}
	if (key == SP_KEY || key == SP)
		if (mlx->flying)
			mlx->player.velocity.z = 0;
	return (0);
}
