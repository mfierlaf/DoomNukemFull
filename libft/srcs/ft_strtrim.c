/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 10:33:57 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/17 10:33:58 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dst;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	j = 0;
	k = 0;
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
		j++;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
		i--;
	if (s[j] == '\0')
		return (ft_strnew(0));
	if ((dst = (malloc(sizeof(char) * (i - j + 2)))) == NULL)
		return (NULL);
	while (k + j < i + 1)
	{
		dst[k] = s[k + j];
		k++;
	}
	dst[k] = '\0';
	return (dst);
}
