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
	//mlx->mouse_map.x = (float)((float)x - (float)mlx->editor.off_x - ((float)mlx->editor.sqr_size / 2.0)) / (float)mlx->editor.sqr_size;
	//mlx->mouse_map.y = (float)((float)y - (float)mlx->editor.off_y - ((float)mlx->editor.sqr_size / 2.0)) / (float)mlx->editor.sqr_size;
	mlx->mouse_map.x = (x - mlx->editor.off_x - (mlx->editor.sqr_size / 2)) / mlx->editor.sqr_size;
	mlx->mouse_map.y = (y - mlx->editor.off_y - (mlx->editor.sqr_size / 2)) / mlx->editor.sqr_size;
	mlx->mouse_map.x *= -1.0;
	mlx->mouse_map.y *= -1.0;
	if (mlx->editor.on == 1 && mlx->events.but1 == 1)
	{
		mlx->editor.off_x += (x - mlx->editor.old_x);
		mlx->editor.off_y += (y - mlx->editor.old_y);
		mlx->editor.old_x = x;
		mlx->editor.old_y = y;
	}
	return (0);
}

int		ft_key_hook(int key, t_mlx *mlx)
{
	if (key == ESC_KEY || key == ESC)
		kill_mlx("", mlx);
	if (key == UP_KEY || key == W_KEY || key == UP_ARROW || key == W_LN)
		mlx->wasd[0] = 1;
	if (key == LEFT_KEY || key == A_KEY || key == LEFT_ARROW || key == A_LN)
		mlx->wasd[1] = 1;
	if (key == DOWN_KEY || key == S_KEY || key == DOWN_ARROW || key == S_LN)
		mlx->wasd[2] = 1;
	if (key == RIGHT_KEY || key == D_KEY || key == RIGHT_ARROW || key == D_LN)
		mlx->wasd[3] = 1;
	if (mlx->editor.on && (key == D_KEY ||key == D_LN))
		mlx->events.new_sector = !mlx->events.new_sector;
	if (key == SP_KEY || key == SP)
	{
		if (mlx->ground)
		{
			mlx->player.velocity.z += 0.5;
			mlx->falling = 1;
		}
	}
	if (key == LCTRL_KEY || key == LCTRL)
	{
		mlx->ducking = 1;
		mlx->moving = 1;
	}
	if (key == R_KEY || R_LN)
		if (mlx->editor.on)
			clear_img(mlx->editor.data_map, mlx->editor.map_img_width, H);
	// shoot_key(key, mlx);
	menu_key_hook(key, mlx);
	return (0);
}
int                mouse_release(int key, int x, int y, t_mlx *mlx)
{
	if (key == BUT1_KEY)
	{
		mlx->events.but1 = 0;;
	}
	return (0);
}
void			shoot_key(int key, int x, int y, t_mlx *mlx)
{
	x++;
	y++;
	if (key == BUT1_KEY)
	{
		if (mlx->editor.on)
		{
			mlx->events.but1 = 1;
			mlx->editor.old_x = x;
			mlx->editor.old_y = y;
			// if (x < mlx->editor.map_img_width && mlx->events.draw_line)
			// {
			// 	if (mlx->editor.start.x == -1)
			// 	{
			// 		mlx->editor.start.x = (x % mlx->editor.sqr_size > (mlx->editor.sqr_size - 1) /2) ? x + (mlx->editor.sqr_size - 1 - (x % mlx->editor.sqr_size)) : x - (x % mlx->editor.sqr_size);
			// 		mlx->editor.start.y = (y % mlx->editor.sqr_size > (mlx->editor.sqr_size - 1) /2) ? y + (mlx->editor.sqr_size - 1 - (y % mlx->editor.sqr_size)) : y - (y % mlx->editor.sqr_size);
			// 		ft_printf("start. x = %d, start.y = %d\n------------------------------\n", mlx->editor.start.x / mlx->editor.sqr_size, mlx->editor.start.y / mlx->editor.sqr_size);
			// 	}
			// 	else
			// 	{
			// 		mlx->editor.end.x = (x % mlx->editor.sqr_size > (mlx->editor.sqr_size - 1) /2) ? x + (mlx->editor.sqr_size - 1 - (x % mlx->editor.sqr_size)): x - (x % mlx->editor.sqr_size);
			// 		mlx->editor.end.y = (y % mlx->editor.sqr_size > (mlx->editor.sqr_size - 1) /2) ? y + (mlx->editor.sqr_size - 1 - (y % mlx->editor.sqr_size)): y - (y % mlx->editor.sqr_size);
			// 		ft_printf("end. x = %d, end.y = %d\n------------------------------\n", (mlx->editor.end.x + (mlx->editor.sqr_size / 2)) / mlx->editor.sqr_size, (mlx->editor.end.y + (mlx->editor.sqr_size / 2)) / mlx->editor.sqr_size);
			// 		bresenham(mlx, 0xFF0000);
			// 		//ft_printf("start. x = %d, start.y = %d\n end.x = %d, end.y = %d\n------------------------------\n", mlx->editor.start.x / mlx->editor.sqr_size, mlx->editor.start.y / mlx->editor.sqr_size, mlx->editor.end.x / mlx->editor.sqr_size, mlx->editor.end.y / mlx->editor.sqr_size);
			// 		mlx->editor.start.x = mlx->editor.end.x;
			// 		mlx->editor.start.y = mlx->editor.end.y;
			// 	}
			//}
		}
		else
		{
			if (mlx->inventory.ammo || mlx->weapon.anim == 15)
			{
				if (mlx->weapon.anim < 15)
				{
					if (!mlx->music.mute)
						system("afplay ./music/gun.mp3 &");
					// mlx->anim.shoot = 1;
					mlx->inventory.ammo--;
					// 	shoot_direction(mlx);
				}
				// shoot(mlx);
				else if (mlx->weapon.anim <= 15 && !mlx->music.mute)
					system("afplay ./music/stab.mp3 &");
				mlx->anim.started = 1;
			}
			else if (mlx->weapon.anim < 15 && !mlx->music.mute)
				system("afplay ./music/click.mp3 &");
		}
	}
	if (key == BUT3_KEY)
	{
		if (mlx->editor.on)
		{
			mlx->editor.start.x = -1;
			mlx->editor.start.y = -1;
		}
	}
	if (key == SCROLLUP_KEY && mlx->editor.on && mlx->editor.sqr_size > 1)
        mlx->editor.sqr_size -= 1;
    if (key == SCROLLDOWN_KEY && mlx->editor.on)
        mlx->editor.sqr_size += 1;
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
		mlx->ducking = 0;
		mlx->moving = 0;
	}
	return (0);
}
