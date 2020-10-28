/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:58:48 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/26 17:39:40 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

int   mouse_hook(int x, int y, t_mlx *mlx)
{
//   if (x < 0 || x > W || y < 0 || y > H)
//     mlx_mouse_move(mlx->win, W / 2, H / 2);
  mlx->mouse.x = x;
  mlx->mouse.y = y;
  return (0);
}

int ft_key_hook(int key, t_mlx *mlx)
{
	if (key == ESC)
		kill_mlx(mlx);
	if (key == UP_ARROW)
		mlx->wasd[0] = 1;
	if (key == LEFT_ARROW)
		mlx->wasd[1] = 1;
	if (key == DOWN_ARROW)
		mlx->wasd[2] = 1;
	if (key == RIGHT_ARROW)
		mlx->wasd[3] = 1;
	if (key == SP)
	{
		if (mlx->ground)
    {
			mlx->player.velocity.z += 0.5;
      mlx->falling = 1;
    }
	}
	if (key == LCTRL)
	{
		mlx->ducking = 1;
		mlx->moving = 1;
	}
	return (0);
}

int stop_movement(int key, t_mlx *mlx)
{
	if (key == UP_ARROW)
		mlx->wasd[0] = 0;
	if (key == LEFT_ARROW)
		mlx->wasd[1] = 0;
	if (key == DOWN_ARROW)
		mlx->wasd[2] = 0;
	if (key == RIGHT_ARROW)
		mlx->wasd[3] = 0;
	if (key == LCTRL)
	{
		mlx->ducking = 0;
		mlx->moving = 0;
	}
	return (0);
}
