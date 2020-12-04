/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:51:19 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/09/29 11:52:56 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void	clear_img(t_mlx *mlx)
{
	int i;

	i = -1;
	while (++i < W * H - 1)
		mlx->data[i] = 0x000000;
}

int		kill_mlx(char *message, t_mlx *mlx)
{
	ft_putstr(message);
	system("pkill afplay");
	unload_data(mlx);
	mlx = NULL;
	// TODO free shit
	exit(1);
	return (0);
}

float	yaw(float y, float z, t_mlx *mlx)
{
	return (y + z * mlx->player.yaw);
}

t_pos	new_pos(float x, float y)
{
	t_pos			pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_line	new_line(t_pos orig, t_pos end)
{
	t_line			line;

	line.orig.x = orig.x;
	line.orig.y = orig.y;
	line.end.x = end.x;
	line.end.y = end.y;
	return (line);
}
