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

int		intersect_box(t_pos p0, t_pos p1, t_pos p2, t_pos p3)
{
	if (overlap(p0.x, p1.x, p2.x, p3.x) == 1 &&
		overlap(p0.y, p1.y, p2.y, p3.y) == 1)
		return (1);
	else
		return (0);
}

float	point_side(t_pos p, t_pos start, t_pos end)
{
	return (vxs((end.x) - (start.x), (end.y) -
		(start.y), (p.x) - (start.x), (p.y) - (start.y)));
}

t_xy	intersect(t_pos p0, t_pos p1, t_pos p2, t_pos p3)
{
	t_xy result;

	result.x = vxs(vxs(p0.x, p0.y, p1.x, p1.y), (p0.x) - (p1.x),
		vxs(p2.x, p2.y, p3.x, p3.y), (p2.x) - (p3.x)) /
		vxs((p0.x) - (p1.x), (p0.y) - (p1.y), (p2.x) - (p3.x), (p2.y) - (p3.y));
	result.y = vxs(vxs(p0.x, p0.y, p1.x, p1.y), (p0.y) - (p1.y),
		vxs(p2.x, p2.y, p3.x, p3.y), (p2.y) - (p3.y)) /
		vxs((p0.x) - (p1.x), (p0.y) - (p1.y), (p2.x) - (p3.x), (p2.y) - (p3.y));
	return (result);
}

float	get_slope(t_line line)
{
	if (line.end.x != line.orig.x)
		return ((line.end.y - line.orig.y) / (line.end.x - line.orig.x));
	return (INFINITY);
}

char	check_valid_inter(t_pos inter, t_line line1, t_line line2)
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

/*struct xy	Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    return (vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)));
}*/
