/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:51:19 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/09/29 11:52:56 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	clamp(double a, double b, double c)
{
	return (min(max(a, b), c));
}

float	vxs(float a, float b, float c, float d)
{
	return ((a) * (d) - (c) * (b));
}

int		overlap(double a, double b, double c, double d)
{
	if (min(a, b) <= max(c, d) && min(c, d) <= max(a, b))
		return (1);
	else
		return (0);
}

int		intersect_box(double x0, double y0, double x1, double y1,
	double x2, double y2, double x3, double y3)
{
	if (overlap(x0, x1, x2, x3) == 1 &&
		overlap(y0, y1, y2, y3) == 1)
		return (1);
	else
		return (0);
}

double	point_side(double px, double py, double x0, double y0, double x1, double y1)
{
	return (vxs((x1) - (x0), (y1) - (y0), (px) - (x0), (py) - (y0)));
}

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

t_xy	intersect(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4)
{
	t_xy result;

	result.x = vxs(vxs(x1, y1, x2, y2), (x1) - (x2),
		vxs(x3, y3, x4, y4), (x3) - (x4)) /
		vxs((x1) - (x2), (y1) - (y2), (x3) - (x4), (y3) - (y4));
	result.y = vxs(vxs(x1, y1, x2, y2), (y1) - (y2),
		vxs(x3, y3, x4, y4), (y3) - (y4)) /
		vxs((x1) - (x2), (y1) - (y2), (x3) - (x4), (y3) - (y4));
	return (result);
}

t_pos				new_pos(float x, float y)
{
	t_pos			pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

t_line				new_line(t_pos orig, t_pos end)
{
	t_line			line;

	line.orig.x = orig.x;
	line.orig.y = orig.y;
	line.end.x = end.x;
	line.end.y = end.y;
	return (line);
}

float				get_slope(t_line line)
{
	if (line.end.x != line.orig.x)
		return ((line.end.y - line.orig.y) / (line.end.x - line.orig.x));
	return (INFINITY);
}

char				check_valid_inter(t_pos inter, t_line line1, t_line line2)
{
	if (line1.orig.x < line1.end.x && (inter.x > line1.end.x ||
				inter.x < line1.orig.x))
		return (0);
	if (line1.orig.x > line1.end.x && (inter.x < line1.end.x ||
				inter.x > line1.orig.x))
		return (0);
	if (line1.orig.y < line1.end.y && (inter.y > line1.end.y ||
				inter.y < line1.orig.y))
		return (0);
	if (line1.orig.y > line1.end.y && (inter.y < line1.end.y ||
				inter.y > line1.orig.y))
		return (0);
	if (line2.orig.x < line2.end.x && (inter.x > line2.end.x ||
				inter.x < line2.orig.x))
		return (0);
	if (line2.orig.x > line2.end.x && (inter.x < line2.end.x ||
				inter.x > line2.orig.x))
		return (0);
	if (line2.orig.y < line2.end.y && (inter.y > line2.end.y ||
				inter.y < line2.orig.y))
		return (0);
	if (line2.orig.y > line2.end.y && (inter.y < line2.end.y ||
				inter.y > line2.orig.y))
		return (0);
	return (1);
}

t_pos				get_intersection(t_line line1, t_line line2, float slope1,
							float slope2)
{
	t_pos			inter;
	float			c1;
	float			c2;

	c1 = line1.orig.y - slope1 * line1.orig.x;
	c2 = line2.orig.y - slope2 * line2.orig.x;
	if (slope1 == slope2)
	{
		inter.x = INFINITY;
		inter.y = INFINITY;
	}
	else if (isinf(slope1) && !isinf(slope2))
	{
		inter.x = line1.orig.x;
		inter.y = slope2 * inter.x + c2;
	}
	else if (!isinf(slope1) && isinf(slope2))
	{
		inter.x = line2.orig.x;
		inter.y = slope1 * inter.x + c1;
	}
	else
	{
		inter.x = (c2 - c1) / (slope1 - slope2);
		inter.y = slope1 * inter.x + c1;
	}
	if (slope1 * slope2 == -1)
	{
		inter.x = (c2 - c1) / (slope1 - slope2);
		inter.y = slope1 * inter.x + c1;
	}
	if (!check_valid_inter(inter, line1, line2))
	{
		inter.x = NAN;
		inter.y = NAN;
	}
	return (inter);
}

float	get_dist(t_pos p1, t_pos p2)
{
	return ((float)sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
			(p2.y - p1.y) * (p2.y - p1.y)));
}

float				get_angle(t_pos p1, t_pos rel_dir)
{
	t_pos			rel_pos;

	rel_pos.x = rel_dir.x - p1.x;
	rel_pos.y = p1.y - rel_dir.y;
	return (atan2f(rel_pos.y, rel_pos.x));
}

int				valid_pixel(int x, int y)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		return (1);
	return (0);
}
