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

int		ft_key_hook(int key, t_mlx *mlx)
{
	if (key == ESC_KEY || key == ESC)
		kill_mlx(mlx);
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
	}
	if (key == LCTRL_KEY)
	{
		mlx->ducking = 1;
		mlx->moving = 1;
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
	if (key == LCTRL_KEY)
	{
		mlx->ducking = 0;
		mlx->moving = 0;
	}
	return (0);
}