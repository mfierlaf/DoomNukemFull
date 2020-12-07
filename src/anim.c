/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fverhuls <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:51 by fverhuls          #+#    #+#             */
/*   Updated: 2019/10/10 13:07:38 by fverhuls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void				shoot_anim(t_mlx *mlx)
{
	int		zoom;
	t_point	coord;

	zoom = W / 213.3;
	if (mlx->anim.started == 1)
	{
		mlx->weapon.anim++;
		if (mlx->weapon.anim % 5 == 0)
		{
			mlx->weapon.anim -= 5;
			mlx->anim.started = 0;
		}
	}
	coord.x = W / 2 - mlx->tab_anim[mlx->weapon.anim]->header.width_px *
		zoom / 2;
	coord.y = H - mlx->tab_anim[mlx->weapon.anim]->header.height_px * zoom;
	draw_image(coord, zoom, mlx->tab_anim[mlx->weapon.anim], mlx);
}

void				sprite_anim_death(int sprite, t_mlx *mlx)
{
	if (mlx->sleep.death >= 30000)
	{
		mlx->objects[mlx->objects[sprite].order].tex =
		mlx->objects[mlx->objects[sprite].order].initial_tex
		+ mlx->anim.curr_anim;
		if (mlx->anim.curr_anim <
			mlx->objects[mlx->objects[sprite].order].nb_anim - 1)
			mlx->anim.curr_anim++;
		else
		{
			mlx->objects[mlx->objects[sprite].order].isbot = 0;
			mlx->anim.curr_anim = 0;
		}
		mlx->sleep.death = 0;
	}
}

void				sprite_anim_walk(int sprite, t_mlx *mlx)
{
	if (mlx->sleep.walk >= 30000)
	{
		mlx->objects[mlx->objects[sprite].order].tex =
		mlx->objects[mlx->objects[sprite].order].initial_tex
		+ mlx->anim.curr_anim_walk;
		if (mlx->anim.curr_anim_walk <
		mlx->objects[mlx->objects[sprite].order].nb_anim_walk - 1)
			mlx->anim.curr_anim_walk++;
		else
			mlx->anim.curr_anim_walk = 0;
		mlx->sleep.walk = 0;
	}
}
