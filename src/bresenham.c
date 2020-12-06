/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-brit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:42:06 by tde-brit          #+#    #+#             */
/*   Updated: 2019/08/03 13:11:51 by tde-brit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	dashed_bresenham(t_mlx *mlx, int color)
{
	int i;

	i = 0;
	mlx->bham.dx = abs(mlx->editor.end.x - mlx->editor.start.x);
	mlx->bham.sx = mlx->editor.start.x < mlx->editor.end.x ? 1 : -1;
	mlx->bham.dy = abs(mlx->editor.end.y - mlx->editor.start.y);
	mlx->bham.sy = mlx->editor.start.y < mlx->editor.end.y ? 1 : -1;
	mlx->bham.err = (mlx->bham.dx > mlx->bham.dy ? mlx->bham.dx :
		-mlx->bham.dy) / 2;
	while (1)
	{
		if (mlx->editor.start.y >= 0 && mlx->editor.start.x >= 0 &&
			 mlx->editor.start.y < H && mlx->editor.start.x < 
			mlx->editor.map_img_width && i < 2)
			mlx->editor.data_map[(int)mlx->editor.start.y * 
				mlx->editor.map_img_width + 
				(int)mlx->editor.start.x] = color;
		if (mlx->editor.start.x == mlx->editor.end.x &&
			mlx->editor.start.y == mlx->editor.end.y)
			break ;
		mlx->bham.e2 = mlx->bham.err;
		if (mlx->bham.e2 > -mlx->bham.dx)
		{
			mlx->bham.err -= mlx->bham.dy;
			mlx->editor.start.x += mlx->bham.sx;
		}
		if (mlx->bham.e2 < mlx->bham.dy)
		{
			mlx->bham.err += mlx->bham.dx;
			mlx->editor.start.y += mlx->bham.sy;
		}
		if (i < 3)
			i++;
		else
			i = 0;
	}
}

void	bresenham(t_mlx *mlx, int color)
{
	mlx->bham.dx = abs(mlx->editor.end.x - mlx->editor.start.x);
	mlx->bham.sx = mlx->editor.start.x < mlx->editor.end.x ? 1 : -1;
	mlx->bham.dy = abs(mlx->editor.end.y - mlx->editor.start.y);
	mlx->bham.sy = mlx->editor.start.y < mlx->editor.end.y ? 1 : -1;
	mlx->bham.err = (mlx->bham.dx > mlx->bham.dy ? mlx->bham.dx :
		-mlx->bham.dy) / 2;
	while (1)
	{
		if (mlx->editor.start.y >= 0 && mlx->editor.start.x >= 0 &&
			 mlx->editor.start.y < H && mlx->editor.start.x < 
			mlx->editor.map_img_width)
			mlx->editor.data_map[(int)mlx->editor.start.y * 
			mlx->editor.map_img_width + (int)mlx->editor.start.x] = color;
		if (mlx->editor.start.x == mlx->editor.end.x &&
			 mlx->editor.start.y == mlx->editor.end.y)
			break ;
		mlx->bham.e2 = mlx->bham.err;
		if (mlx->bham.e2 > -mlx->bham.dx)
		{
			mlx->bham.err -= mlx->bham.dy;
			mlx->editor.start.x += mlx->bham.sx;
		}
		if (mlx->bham.e2 < mlx->bham.dy)
		{
			mlx->bham.err += mlx->bham.dx;
			mlx->editor.start.y += mlx->bham.sy;
		}
	}
}

