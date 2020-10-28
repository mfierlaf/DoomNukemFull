/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 16:25:21 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/23 16:51:28 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;
	char	*a;
	char	*b;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	a = (char*)s1;
	b = (char*)s2;
	i = 0;
	j = 0;
	if (!(res = malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 1))))
		return ((void*)0);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i++] = s2[j++];
	}
	res[i] = '\0';
	return (res);
}
