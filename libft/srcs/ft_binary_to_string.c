/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_to_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdelvenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:49:07 by sdelvenn          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:13 by sdelvenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void ft_binary_to_string(char **string, char *binary)
{
	char *tmp;

	*string = malloc(strlen(binary) / 9 + 1);

	if(*string == NULL)
		exit(1);

	tmp = *string;
	while(*binary)
	{
		ft_binary_to_char(binary, tmp);
		binary += 9;
		tmp++;
	}
	*tmp = 0;
	//free(octet);
}