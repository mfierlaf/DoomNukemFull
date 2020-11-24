/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_to_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdelvenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:49:07 by sdelvenn          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:13 by sdelvenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void ft_binary_to_char(char *chaine, char *pt_char)
{
	int character;
	int i;

	i = 7;
	character = 0;
	while(i >= 0)
	{
		if(*chaine == '1')
			character += ft_pow(2, i);
		i--;
		chaine++;
	}
	*pt_char = (char)character;
}
