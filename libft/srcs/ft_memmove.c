/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:29:46 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/18 16:40:51 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*res;
	unsigned char	*origin;
	int				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	res = (unsigned char*)dst;
	origin = (unsigned char*)src;
	i = 0;
	if (dst > src)
	{
		len--;
		while ((int)len >= 0)
		{
			res[len] = origin[len];
			len--;
		}
		return (res);
	}
	while (i < (int)len)
	{
		res[i] = origin[i];
		i++;
	}
	return (res);
}
