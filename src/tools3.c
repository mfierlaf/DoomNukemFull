/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
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
