/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 07:55:49 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/11/23 14:15:46 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int n)
{
	int		i;
	int		u;
	char	*conc_str;

	if (!s1 || !s2 || n < 0 || n > 3)
		return (NULL);
	i = -1;
	if ((conc_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		while (s1[++i])
			conc_str[i] = s1[i];
		if (n == 1 || n == 3)
			free((char *)s1);
		u = -1;
		while (s2[++u])
			conc_str[i++] = s2[u];
		if (n == 2 || n == 3)
			free((char *)s2);
		conc_str[i] = '\0';
	}
	return (conc_str);
}
