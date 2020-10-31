/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <cvan-duf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:07:15 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/09/30 14:40:55 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void			draw_pixel(int x, int y, t_mlx *mlx)
{
	if (x >= 0 && x <= W &&
		y >= 0 && y <= H &&
		W * y + x < W * H - 1)
		mlx->data[W * y + x] = 0xff0000;
}

void			line(int x0, int y0, int x1, int y1, t_mlx *mlx)
{
	int		e2;
	int		err;
	t_point d;
	t_point s;

	d.x = abs(x1 - x0);
	s.x = x0 < x1 ? 1 : -1;
	d.y = abs(y1 - y0);
	s.y = y0 < y1 ? 1 : -1;
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while (!(x0 == x1 && y0 == y1))
	{
		draw_pixel(x0, y0, mlx);
		e2 = err;
		if (e2 > -d.x)
		{
			err -= d.y;
			x0 += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			y0 += s.y;
		}
	}
}

void			draw_rect(t_point size, int x, int y, t_mlx *mlx)
{
	line(x, y, x, y + size.y, mlx);
	line(x, y, x + size.x, y, mlx);
	line(x + size.x, y, x + size.x, y + size.y, mlx);
	line(x, y + size.y, x + size.x, y + size.y, mlx);
}

void			filled_rect(t_point size, int x, int y, t_mlx *mlx)
{
	int draw_x;

	draw_x = x;
	while (draw_x <= x + size.x)
	{
		line(draw_x, y, draw_x, y + size.y, mlx);
		draw_x++;
	}
}
