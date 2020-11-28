/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:06:10 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/18 15:49:14 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*res;
	unsigned char	*origin;
	unsigned char	cc;
	size_t			i;

	res = (unsigned char*)dst;
	origin = (unsigned char*)src;
	i = 0;
	cc = (unsigned char)c;
	while (i < n)
	{
		if (origin[i] == cc)
		{
			res[i] = origin[i];
			return (res + i + 1);
		}
		res[i] = origin[i];
		i++;
	}
	return (NULL);
}
