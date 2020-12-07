/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jreynaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:51 by jreynaer          #+#    #+#             */
/*   Updated: 2019/10/10 13:07:38 by jreynaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void	shoot_while2(t_shoot *shoot, t_mlx *mlx)
{
	if (!isnan(shoot->inter.x) && mlx->objects[
			mlx->objects[shoot->sprite].order].life > 0)
	{
		mlx->objects[mlx->objects[shoot->sprite].order].life -=
			mlx->weapon.damage;
		if (mlx->objects[mlx->objects[shoot->sprite].order].life <= 0)
		{
			mlx->objects[mlx->objects[shoot->sprite].order].initial_tex =
				mlx->objects[mlx->objects[shoot->sprite].order].initial_tex +
				mlx->objects[mlx->objects[shoot->sprite].order].nb_anim_walk;
			mlx->objects[mlx->objects[shoot->sprite].order].isbot = 2;
		}
		if (!mlx->music.mute)
			system("afplay ./music/death.mp3 &");
	}
}

void		shoot_while(t_shoot *shoot, t_mlx *mlx)
{
	if (mlx->weapon.anim >= 15)
		shoot->inter = get_intersection(shoot->straight_ray,
				mlx->objects[mlx->objects[shoot->sprite].order].sprite_line,
				get_slope(shoot->straight_ray),
				get_slope(mlx->objects[mlx->objects[
					shoot->sprite].order].sprite_line));
	else
		shoot->inter = get_intersection(shoot->small_ray,
				mlx->objects[mlx->objects[shoot->sprite].order].sprite_line,
				get_slope(shoot->small_ray),
				get_slope(mlx->objects[mlx->objects[
					shoot->sprite].order].sprite_line));
	shoot_while2(shoot, mlx);
}
