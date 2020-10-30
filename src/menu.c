/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:14:25 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 14:14:27 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

// void		menu(t_var *var)
// {
// 	t_point coord;

// 	coord.x = 100;
// 	coord.y = -110;
// 	draw_image(coord, 0.3, var->tab_bmp[13], var);
// 	coord.x = -WIN_L + 100;
// 	coord.y = -110;
// 	draw_image(coord, 0.3, var->tab_bmp[13], var);
// 	menu_gun(var);
// 	if (var->music.mute == 1)
// 	{
// 		coord.x = WIN_L / 25.6;
// 		coord.y = WIN_H / 1.2;
// 		draw_image(coord, 0.5, var->tab_sprite[85], var);
// 	}
// }