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

t_point			new_point(int x, int y)
{
	t_point p;

	p.x = x;
	p.y = y;
	return (p);
}

void			line(t_point o, t_point e, t_mlx *mlx)
{
	int		e2;
	int		err;
	t_point d;
	t_point s;

	d.x = abs(e.x - o.x);
	s.x = o.x < e.x ? 1 : -1;
	d.y = abs(e.y - o.y);
	s.y = o.y < e.y ? 1 : -1;
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while (!(o.x == e.x && o.y == e.y))
	{
		draw_pixel(o.x, o.y, mlx);
		e2 = err;
		if (e2 > -d.x)
		{
			err -= d.y;
			o.x += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			o.y += s.y;
		}
	}
}

void			draw_rect(t_point size, int x, int y, t_mlx *mlx)
{
	line(new_point(x, y), new_point(x, y + size.y), mlx);
	line(new_point(x, y), new_point(x + size.x, y), mlx);
	line(new_point(x + size.x, y), new_point(x + size.x, y + size.y), mlx);
	line(new_point(x, y + size.y), new_point(x + size.x, y + size.y), mlx);
}

void			filled_rect(t_point size, int x, int y, t_mlx *mlx)
{
	int draw_x;

	draw_x = x;
	while (draw_x <= x + size.x)
	{
		line(new_point(draw_x, y), new_point(draw_x, y + size.y), mlx);
		draw_x++;
	}
}
