/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_to_binary.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdelvenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:49:07 by sdelvenn          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:13 by sdelvenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_char_to_binary(int character, char *octet)
{
	int i;

	i = 8;
	while (i > 0)
	{
		*octet = '0';
		octet++;
		i--;
	}
	while (character > 0)
	{
		--octet;
		*octet = character % 2 + '0';
		character = character / 2;
	}
	if (character == 0)
	{
		--octet;
		*octet = '0';
	}
}
