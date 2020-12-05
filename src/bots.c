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
	if (mlx->objects[mlx->objects[sprite].order].life >= 0)
	{
		mlx->objects[mlx->objects[sprite].order].pos.x += (mlx->player.where.x -
			mlx->objects[mlx->objects[sprite].order].pos.x) * 0.000005;
		mlx->objects[mlx->objects[sprite].order].pos.y += (mlx->player.where.y -
			mlx->objects[mlx->objects[sprite].order].pos.y) * 0.000005;
	}
}

void				bot_shooting(int sprite, t_mlx *mlx)
{
	t_line		shot;
	t_pos		in;
	t_pos		pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	if (mlx->sleep.shoot >= mlx->menu.bot_level)
	{
		shot = new_line(mlx->objects[mlx->objects[sprite].order].pos,
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

static void			bot_wds(t_mlx *mlx, int sprite)
{
	if (mlx->objects[mlx->objects[sprite].order].isbot)
	{
		mlx->sleep.walk++;
		mlx->sleep.death++;
		mlx->sleep.shoot++;
	}
}

void				bot(int sprite, t_mlx *mlx)
{
	float dist_bot;
	t_pos pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	if (mlx->objects[mlx->objects[sprite].order].life)
	{
		dist_bot =
		get_dist(pl_pos, mlx->objects[mlx->objects[sprite].order].pos);
		mlx->sleep.shoot++;
	}
	if (mlx->objects[mlx->objects[sprite].order].life && mlx->player.sector ==
		mlx->objects[mlx->objects[sprite].order].sector)
		moving_bot(sprite, mlx);
	bot_wds(mlx, sprite);
	if (mlx->objects[mlx->objects[sprite].order].isbot == 1)
	{
		sprite_anim_walk(sprite, mlx);
		if (dist_bot < 5 && mlx->player.sector ==
			mlx->objects[mlx->objects[sprite].order].sector)
			bot_shooting(sprite, mlx);
	}
	if (mlx->objects[mlx->objects[sprite].order].isbot == 2)
		sprite_anim_death(sprite, mlx);
}
