/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:49:45 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/22 10:57:16 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*final;

	if ((final = (void*)malloc(sizeof(void) * size)) == NULL)
		return ((void*)0);
	ft_memset(final, 0, size);
	return (final);
}
