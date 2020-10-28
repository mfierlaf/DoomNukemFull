/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	init(t_mlx *mlx)
{
	mlx->moving = 0;
	mlx->wasd[0] = 0;
	mlx->wasd[1] = 0;
	mlx->wasd[2] = 0;
	mlx->wasd[3] = 0;
	mlx->ground = 0;
	mlx->falling = 0;
	mlx->ducking = 0;
	mlx->sectors = NULL;
	mlx->num_sectors = 0;
}
