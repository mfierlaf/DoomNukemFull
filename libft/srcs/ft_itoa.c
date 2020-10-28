/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:19:06 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/22 10:21:40 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static int	taille(long n)
{
	int cpt;

	cpt = 0;
	if (n <= 0)
		cpt++;
	while (n != 0)
	{
		n = n / 10;
		cpt++;
	}
	return (cpt);
}

char		*ft_itoa(int n)
{
	long	i;
	int		cpt;
	char	*res;

	i = (long)n;
	cpt = taille(i);
	if ((res = (char*)malloc(sizeof(char) * (cpt + 1))) == NULL)
		return ((void*)0);
	res[cpt] = '\0';
	cpt--;
	if (i < 0)
	{
		res[0] = '-';
		i *= -1;
	}
	if (i == 0 || i == -0)
		res[0] = '0';
	while (i > 0)
	{
		res[cpt] = (i % 10) + '0';
		i = i / 10;
		cpt--;
	}
	return (res);
}
