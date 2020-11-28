/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:55:45 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/23 12:55:50 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*final;
	int		i;
	int		j;

	if (s == NULL || f == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
		i++;
	if ((final = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
		return ((void*)0);
	while (s[j] != '\0')
	{
		final[j] = f(j, s[j]);
		j++;
	}
	final[j] = '\0';
	return (final);
}
