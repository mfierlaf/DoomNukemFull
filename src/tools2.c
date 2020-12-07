/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:51:19 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/09/29 11:52:56 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static t_pos		get_inter(t_inter data)
{
	t_pos	inter;

	if (data.slope1 == data.slope2)
	{
		inter.x = INFINITY;
		inter.y = INFINITY;
	}
	else if (isinf(data.slope1) && !isinf(data.slope2))
	{
		inter.x = data.line1.orig.x;
		inter.y = data.slope2 * inter.x + data.c2;
	}
	else if (!isinf(data.slope1) && isinf(data.slope2))
	{
		inter.x = data.line2.orig.x;
		inter.y = data.slope1 * inter.x + data.c1;
	}
	else
	{
		inter.x = (data.c2 - data.c1) / (data.slope1 - data.slope2);
		inter.y = data.slope1 * inter.x + data.c1;
	}
	return (inter);
}

t_pos				get_intersection(t_line line1, t_line line2, float slope1,
							float slope2)
{
	t_pos			inter;
	t_inter			data;

	data.line1 = line1;
	data.line2 = line2;
	data.slope1 = slope1;
	data.slope2 = slope2;
	data.c1 = data.line1.orig.y - data.slope1 * data.line1.orig.x;
	data.c2 = data.line2.orig.y - data.slope2 * data.line2.orig.x;
	inter = get_inter(data);
	if (data.slope1 * data.slope2 == -1)
	{
		inter.x = (data.c2 - data.c1) / (data.slope1 - data.slope2);
		inter.y = data.slope1 * inter.x + data.c1;
	}
	if (!check_valid_inter(inter, data.line1, data.line2))
	{
		inter.x = NAN;
		inter.y = NAN;
	}
	return (inter);
}

float				get_dist(t_pos p1, t_pos p2)
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

int					valid_pixel(int x, int y)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		return (1);
	return (0);
}
