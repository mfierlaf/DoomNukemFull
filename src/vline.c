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

t_vl			new_vl(int x, int y1, int y2, unsigned txtx)
{
	t_vl vl;

	vl.x = x;
	vl.y1 = y1;
	vl.y2 = y2;
	vl.txtx = txtx;
	return (vl);
}

t_scale			new_scale(int a, int b, int c, t_point df)
{
	t_scale scale;

	scale.a = a;
	scale.b = b;
	scale.c = c;
	scale.d = df.x;
	scale.f = df.y;
	return (scale);
}

t_scaler		scaler_init(t_scale scale)
{
	t_scaler scaler;

	scaler.result = scale.d + (scale.b - 1 -
		scale.a) * (scale.f - scale.d) / (scale.c - scale.a);
	scaler.bop = ((scale.f < scale.d) ^
		(scale.c < scale.a)) ? -1 : 1;
	scaler.fd = abs(scale.f - scale.d);
	scaler.ca = abs(scale.c - scale.a);
	scaler.cache = (int)((scale.b - 1 - scale.a) *
		abs(scale.f - scale.d)) % abs(scale.c - scale.a);
	return (scaler);
}

int				scaler_next(t_scaler *i)
{
	i->cache += i->fd;
	while (i->cache >= i->ca)
	{
		i->result += i->bop;
		i->cache -= i->ca;
	}
	return (i->result);
}

void			vertical_line(t_draw *draw, t_vl vl, t_scaler ty, t_mlx *mlx)
{
	int	color;
	int	y;

	vl.y1 = clamp(vl.y1, 0, H - 1);
	vl.y2 = clamp(vl.y2, 0, H - 1);
	y = vl.y1;
	while (y <= vl.y2)
	{
		mlx->txty = scaler_next(&ty);
		color = get_color(mlx->tab_bmp[draw->tex],
			(vl.txtx % mlx->tab_bmp[draw->tex]->header.width_px),
			(mlx->txty % mlx->tab_bmp[draw->tex]->header.height_px));
		if (mlx->sectors[draw->now.sectorno].brightness == 0)
			color = (color >> 1) & 8355711;
		if (color != FILTER_COLOR)
			mlx->data[y * W + vl.x] = color;
		y++;
	}
}
