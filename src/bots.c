/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fverhuls <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:51 by fverhuls          #+#    #+#             */
/*   Updated: 2019/10/10 13:07:38 by fverhuls         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void				moving_bot(int sprite, t_mlx *mlx)
{
	if (mlx->objects[sprite].life >= 0)
	{
		mlx->objects[sprite].pos.x += (mlx->player.where.x -
			mlx->objects[sprite].pos.x) * 0.000005;
		mlx->objects[sprite].pos.y += (mlx->player.where.y -
			mlx->objects[sprite].pos.y) * 0.000005;
	}
}

void				bot_shooting(int sprite, t_mlx *mlx)
{
	t_line			shot;
	t_pos			in;
	t_pos pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	if (mlx->sleep.shoot >= mlx->menu.bot_level)
	{
		shot = new_line(mlx->objects[sprite].pos,
			pl_pos);
		in = get_intersection(shot, new_line(new_pos(pl_pos.x,
			pl_pos.y), new_pos(pl_pos.x, pl_pos.y)),
		get_slope(shot), get_slope(new_line(new_pos(pl_pos.x,
			pl_pos.y), new_pos(pl_pos.x, pl_pos.y))));
		if (!isnan(in.x) && !isnan(in.y))
		{
			if (!mlx->inventory.shield)
				mlx->player.life--;
			else
				mlx->inventory.shield--;
		}
		mlx->sleep.shoot = 0;
	}
}

void				bot(int sprite, t_mlx *mlx)
{
	float dist_bot;
	t_pos pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	if (mlx->objects[sprite].life)
	{
		dist_bot = get_dist(pl_pos, mlx->objects[sprite].pos);
		mlx->sleep.shoot++;
	}
	if (mlx->objects[sprite].life && mlx->player.sector == mlx->objects[sprite].sector) //dist_bot < 5)
		moving_bot(sprite, mlx);
	if (mlx->objects[sprite].isbot)
	{
		mlx->sleep.walk++;
		mlx->sleep.death++;
		mlx->sleep.shoot++;
	}
	if (mlx->objects[sprite].isbot == 1)
	{
		sprite_anim_walk(sprite, mlx);
		if (dist_bot < 5 && mlx->player.sector == mlx->objects[sprite].sector)
			bot_shooting(sprite, mlx);
	}
	if (mlx->objects[sprite].isbot == 2)
		sprite_anim_death(sprite, mlx);
}
