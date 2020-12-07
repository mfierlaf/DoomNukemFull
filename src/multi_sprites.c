/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void		multi_sprites(int sprite, t_mlx *mlx)
{
	float	angle;
	t_pos	pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	angle = get_angle(mlx->objects[mlx->objects[sprite].order].pos,
			pl_pos);
	if (angle >= -M_PI / 8 && angle < M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_1;
	if (angle >= M_PI / 8 && angle < 3 * M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_2;
	if (angle >= 3 * M_PI / 8 && angle < 5 * M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_3;
	if (angle >= 5 * M_PI / 8 && angle < 7 * M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_4;
	if (angle >= 7 * M_PI / 8 && angle < -7 * M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_5;
	if (angle >= -7 * M_PI / 8 && angle < -5 * M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_6;
	if (angle >= -5 * M_PI / 8 && angle < -3 * M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_7;
	if (angle >= -3 * M_PI / 8 && angle < -M_PI / 8)
		mlx->objects[mlx->objects[sprite].order].tex = MULTI_8;
}

int			double_swap(t_mlx *mlx, int i, int j)
{
	ft_swap_float(&(mlx->objects[i].distance), &(mlx->objects[j].distance));
	ft_swap_int(&(mlx->objects[i].order), &(mlx->objects[j].order));
	return (1);
}

void		sort_sprites(t_mlx *mlx)
{
	int	gap;
	int	swapped;
	int	i;
	int	j;

	swapped = 0;
	gap = NB_OBJ;
	while (gap > 1 || swapped)
	{
		swapped = 0;
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		else if (gap < 1)
			gap = 1;
		i = 1;
		while (i < NB_OBJ - gap)
		{
			j = i + gap;
			if (mlx->objects[i].distance < mlx->objects[j].distance)
				swapped = double_swap(mlx, i, j);
			i++;
		}
	}
}
