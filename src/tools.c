/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                             :+:      :+:    :+:   */
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
	return (min(max(a,b), c));
}

double	vxs(double a, double b, double c, double d)
{
	return ((a) * (d) - (c) * (b));
}

int		overlap(double a,double b,double c,double d)
{
	if (min(a,b) <= max(c,d) && min(c,d) <= max(a,b))
		return (1);
	else
		return (0);
}

int		intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
	if (overlap(x0,x1,x2,x3) == 1 && overlap(y0,y1,y2,y3) == 1)
		return (1);
	else
		return (0);
}

double	point_side(double px, double py, double x0, double y0, double x1, double y1)
{
	return (vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)));
}

void 	clear_img(t_mlx *mlx)
{
	int i;

	i = -1;
	while(++i < W * H - 1)
		mlx->data[i] = 0x000000;
}

int kill_mlx(t_mlx *mlx)
{
	system("pkill afplay");
	unload_data(mlx);
	mlx = NULL;
	// TODO free shit

	exit(1);
	return (0);
}

/*struct xy	Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    return (vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)));
}*/
