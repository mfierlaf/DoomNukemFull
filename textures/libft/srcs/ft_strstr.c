/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:30:52 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/09 14:30:57 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int ib;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		ib = 0;
		while (str[i + ib] == to_find[ib])
		{
			if (to_find[ib + 1] == '\0')
				return ((char *)str + i);
			ib++;
		}
		i++;
	}
	return (0);
}
