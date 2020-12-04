/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:14:25 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 14:14:27 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

t_scaler	scaler_init(int a, int b, int c, int d, int f)
{
	t_scaler scaler;

	scaler.result = d + (b - 1 - a) * (f - d) / (c - a);
	scaler.bop = ((f < d) ^ (c < a)) ? -1 : 1;
	scaler.fd = abs(f - d);
	scaler.ca = abs(c - a);
	scaler.cache = (int)((b - 1 - a) * abs(f - d)) % abs(c - a);
	return (scaler);
}

int				scaler_next(t_scaler *i)
{
	for (i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
		i->result += i->bop;
	return (i->result);
}

void			vertical_line(t_draw *draw, int x, int y1, int y2, t_scaler ty, unsigned txtx, t_mlx *mlx)
{
	int color;

	y1 = clamp(y1, 0, H - 1);
	y2 = clamp(y2, 0, H - 1);
	for (int y = y1; y <= y2; ++y)
	{
		mlx->txty = scaler_next(&ty);
		color = get_color(mlx->tab_bmp[draw->tex],
			(txtx % mlx->tab_bmp[draw->tex]->header.width_px),
			(mlx->txty % mlx->tab_bmp[draw->tex]->header.height_px));
		if (mlx->sectors[draw->now.sectorno].brightness == 0)
			color = (color >> 1) & 8355711;
		if (color != FILTER_COLOR)
			mlx->data[y * W + x] = color;
	}
}
