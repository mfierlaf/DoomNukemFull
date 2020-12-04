/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:14:25 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 14:14:27 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void			draw_image(t_point point, float zoom, t_bmp *bmp, t_mlx *mlx)
{
	int		x_draw;
	int		y_draw;
	int		color;

	y_draw = point.y;
	while (y_draw < bmp->header.height_px * zoom + point.y)
	{
		x_draw = point.x;
		while (x_draw < bmp->header.width_px * zoom + point.x)
		{
			if (valid_pixel(x_draw, y_draw))
			{
				color = get_color(bmp,
					(int)(((float)x_draw - point.x) / zoom),
					(int)(((float)y_draw - point.y) / zoom));
				if (color != FILTER_COLOR)
					mlx->data[y_draw * W + x_draw] = color;
			}
			x_draw++;
		}
		y_draw++;
	}
}

void			choose_level(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 2.35, 0xfa2d2d, "Bot:");
	if (mlx->menu.bot_level == 38000)
		mlx_string_put(mlx->mlx, mlx->win, W / 50 + 65,
		H / 2.35, 0xD67B1F, "1");
	else if (mlx->menu.bot_level == 28000)
		mlx_string_put(mlx->mlx, mlx->win, W / 50 + 65,
		H / 2.35, 0xD67B1F, "2");
	else if (mlx->menu.bot_level == 18000)
		mlx_string_put(mlx->mlx, mlx->win, W / 50 + 65,
		H / 2.35, 0xD67B1F, "3");
	else if (mlx->menu.bot_level == 8000)
		mlx_string_put(mlx->mlx, mlx->win, W / 50 + 65,
		H / 2.35, 0xD67B1F, "4");
}

void			choose_music(t_mlx *mlx)
{
	if (mlx->music.music == 0)
	{
		mlx->music.name = "Sandstorm";
		system("afplay ./music/sandstorm.mp3 &");
	}
	else if (mlx->music.music == 1)
	{
		mlx->music.name = "Crab rave";
		system("afplay ./music/crab_rave.mp3 &");
	}
	else if (mlx->music.music == 2)
	{
		mlx->music.name = "Roundabout";
		system("afplay ./music/roundabout.mp3 &");
	}
	else if (mlx->music.music == 3)
	{
		mlx->music.name = "No music";
		system("pkill afplay");
	}
}

void			music(t_mlx *mlx)
{
	mlx->music.name = "Sandstorm";
	if (!mlx->music.mute)
		choose_music(mlx);
	else
	{
		mlx->music.name = "No music";
		system("pkill afplay");
	}
}

void			menu_strings(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 15.36, 0xfa2d2d, "DOOM-NUKEM");
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 4.75, 0xfa2d2d, "Start");
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 3.75, 0xfa2d2d, "Edit map");
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 3.15, 0xfa2d2d, "Mute");
	mlx_string_put(mlx->mlx, mlx->win, W / 50 + 65,
		H / 2.72, 0xD67B1F, mlx->music.name);
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 2.72, 0xfa2d2d, "Music:");
	choose_level(mlx);
	mlx_string_put(mlx->mlx, mlx->win, W / 50, H
		/ 2.05, 0xfa2d2d, "QUIT");
	if (mlx->player.is_dead == 1)
		mlx_string_put(mlx->mlx, mlx->win, W / 25.6, H
		/ 1.50, 0xfa2d2d, "YOU LOST!");
	else if (mlx->player.is_dead == 2)
		mlx_string_put(mlx->mlx, mlx->win, W / 25.6, H
		/ 1.50, 0xfa2d2d, "YOU WON!");
}