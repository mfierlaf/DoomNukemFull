/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 14:11:51 by mfierlaf          #+#    #+#             */
/*   Updated: 2019/10/11 12:07:45 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

int		ft_atoi(const char *str)
{
	long	res;
	int		s;
	long	of;

	s = 1;
	res = 0;
	while (*str == '\t' || *str == '\v' || *str == '\n' || *str == '\r' ||
			*str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0' && (ft_isdigit(*str) == 1))
	{
		of = res;
		res = res * 10 + (*str - '0');
		if (of != 0 && (of ^ res) < 0 && s == -1)
			return (0);
		if (of != 0 && (of ^ res) < 0 && s == 1)
			return (-1);
		str++;
	}
	return ((int)res * s);
}
