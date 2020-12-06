/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_to_binary.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdelvenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 18:49:07 by sdelvenn          #+#    #+#             */
/*   Updated: 2019/02/28 13:26:13 by sdelvenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_string_to_binary(char *text, char **binary)
{
	char	*tmp;
	char	*octet;
	char	*tmp_octet;

	octet = malloc(9);
	*binary = malloc(strlen(text) * 9 + 1);
	if (*binary == NULL)
		exit(1);
	tmp = *binary;
	while (*text)
	{
		tmp_octet = octet;
		ft_char_to_binary(*text, octet);
		while (*tmp_octet)
			*tmp++ = *tmp_octet++;
		*tmp++ = ' ';
		text++;
	}
	*tmp = 0;
}
