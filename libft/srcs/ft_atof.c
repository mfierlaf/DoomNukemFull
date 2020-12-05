/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

double		atof_calc(const char *str, int i, char is_fl_part, double value)
{
	double	iter_floating_part;

	iter_floating_part = 10.0;
	while (str[++i])
	{
		if (ft_isdigit(str[i]))
		{
			if (!is_fl_part)
			{
				if (value)
					value *= 10.0;
				value += (double)(str[i] - '0');
			}
			else
			{
				value += ((double)(str[i] - '0') / iter_floating_part);
				iter_floating_part *= 10.0;
			}
		}
		else if (str[i] == '.')
		{
			is_fl_part = 1;
		}
	}
	return (value);
}

double		ft_atof(const char *str)
{
	int		i;
	char	is_fl_part;
	double	value;
	double	sign;

	is_fl_part = 0;
	i = -1;
	value = 0.0;
	sign = 1.0;
	if (str[0] == '-')
	{
		sign = -1.0;
		i++;
	}
	if (!ft_isdigit(str[i + 1]))
		return (0.0);
	value = atof_calc(str, i, is_fl_part, value);
	return (value * sign);
}
