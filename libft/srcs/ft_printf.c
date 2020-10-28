/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:43:26 by mfierlaf          #+#    #+#             */
/*   Updated: 2019/09/04 15:36:28 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	ft_printf(const char *s, ...)
{
	int		i;
	va_list	argp;

	va_start(argp, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 'd')
				ft_putnbr(va_arg(argp, int));
			else if (s[i] == 's')
				ft_putstr(va_arg(argp, char *));
			else if (s[i] == 'c')
				ft_putchar(va_arg(argp, int));
			i++;
		}
		else
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}
