/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:53:36 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/22 18:13:13 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (s1[i] && i < n)
		i++;
	while (s2[j] != '\0' && (i + j + 1) < n)
	{
		s1[i + j] = s2[j];
		j++;
	}
	if (j + i < n)
		s1[j + i] = '\0';
	return (i + ft_strlen(s2));
}
