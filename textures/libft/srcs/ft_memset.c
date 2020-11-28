/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 15:58:02 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/22 10:28:52 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_memset(void *src, int c, size_t n)
{
	size_t	i;
	char	*b;

	i = 0;
	b = (char *)src;
	while (i < n)
	{
		b[i] = (unsigned char)c;
		i++;
	}
	return (src);
}
