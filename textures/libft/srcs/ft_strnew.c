/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:40:40 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/23 12:59:46 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strnew(size_t size)
{
	char	*final;

	if ((final = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return ((void*)0);
	ft_memset(final, '\0', size + 1);
	return (final);
}
