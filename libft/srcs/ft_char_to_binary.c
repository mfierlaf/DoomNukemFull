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

void ft_char_to_binary(char character, char *octet)
{
	int decimal;
	decimal = (int)character;
	int i;

	i = 8;
	while(i > 0)
	{
		*octet = '0';
		octet++;
		i--;
	}

	while(decimal > 0)
	{
		--octet;
		*octet = decimal % 2 + '0';
		decimal = decimal / 2;
	}

	if(decimal == 0)
	{
		--octet;
		*octet = '0';
	}
}