/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:44:49 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/23 16:51:14 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t i)
{
	size_t j;

	j = 0;
	if (i == 0)
		return (0);
	while (j < i - 1 && s1[j] && s2[j] == s1[j])
	{
		j++;
	}
	return ((unsigned char)s1[j] - (unsigned char)s2[j]);
}
