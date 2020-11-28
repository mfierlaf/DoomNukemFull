/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:21:08 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/22 10:36:24 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*cpy;

	i = 0;
	while (src[i] != '\0')
		i++;
	if ((cpy = malloc(sizeof(char) * (i + 1))) == NULL)
		return ((void*)0);
	cpy[i] = '\0';
	while (i >= 0)
	{
		cpy[i] = src[i];
		i--;
	}
	return (cpy);
}
