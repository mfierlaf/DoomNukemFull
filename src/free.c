/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-brit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void		free_draw(t_draw *draw)
{
	free(draw->renderedsectors);
}

void		free_lines(t_load *load)
{
	int		i;

	i = 0;
	free(load->line);
	while (load->split_line[i])
	{
		free(load->split_line[i]);
		i++;
	}
	free(load->split_line);
}
