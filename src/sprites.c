/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void	vsl_draw(t_mlx *mlx, int x, t_sprites sprite, t_vsl vsl)
{
	if (vsl.dx != 0)
		vsl.dx = (sprite.inter.x - sprite.a.x) / (sprite.b.x - sprite.a.x);
	else
		vsl.dx = (sprite.inter.y - sprite.a.y) / (sprite.b.y - sprite.a.y);
	if (!isnan(vsl.dx) && !isnan(vsl.dy))
	{
		vsl.rel_x = vsl.dx * sprite.curr_bmp->header.width_px;
		vsl.dy = (float)(vsl.y - sprite.draw_start) /
			(float)(sprite.draw_end - sprite.draw_start);
		vsl.rel_y = vsl.dy * sprite.curr_bmp->header.height_px;
		if (valid_pixel(x, vsl.y))
		{
			vsl.color = get_color(sprite.curr_bmp,
					(int)vsl.rel_x, (int)vsl.rel_y);
			if (vsl.color != FILTER_COLOR)
			{
				if (mlx->sectors[mlx->objects[
						mlx->objects[vsl.i].order].sector].brightness == 0)
					vsl.color = (vsl.color >> 1) & 8355711;
				mlx->data[x + vsl.y * W] = vsl.color;
			}
		}
	}
}

void		vertical_sprite_lines(t_mlx *mlx, int x, t_sprites sprite, int i)
{
	t_vsl	vsl;

	vsl.i = i;
	sprite.draw_start = clamp(sprite.draw_start, 0, H - 1) - mlx->mouse.y;
	sprite.draw_end = clamp(sprite.draw_end, 0, H - 1) - mlx->mouse.y;
	vsl.y = sprite.draw_start;
	vsl.y_max = sprite.draw_end;
	while (vsl.y < vsl.y_max)
	{
		vsl_draw(mlx, x, sprite, vsl);
		vsl.y++;
	}
}

static void	draw_sprites_precalc(int x, t_mlx *mlx, int i, t_sprites *sprite)
{
	if (mlx->objects[mlx->objects[i].order].tex >= MULTI_1 &&
			mlx->objects[mlx->objects[i].order].tex <= MULTI_8)
		multi_sprites(i, mlx);
	sprite->sp_pos = new_pos(mlx->objects[mlx->objects[i].order].pos.x,
			mlx->objects[mlx->objects[i].order].pos.y);
	sprite->pl_pos = new_pos(mlx->player.where.x, mlx->player.where.y);
	sprite->dist_ps = get_dist(sprite->pl_pos, sprite->sp_pos);
	sprite->angle = get_angle(sprite->pl_pos, sprite->sp_pos);
	if (sprite->dist_ps < 1.0)
		sprite->dist_ps = 1.0;
	sprite->dist_pa = sqrtf(sprite->dist_ps * sprite->dist_ps + 0.5 * 0.5);
	sprite->off_angle = atanf(0.5 / sprite->dist_ps);
	sprite->a = new_pos(sprite->dist_pa * cosf(sprite->angle +
				sprite->off_angle) + sprite->pl_pos.x,
			sprite->dist_pa * -sinf(sprite->angle +
				sprite->off_angle) + sprite->pl_pos.y);
	sprite->b = new_pos(sprite->dist_pa * cosf(sprite->angle
				- sprite->off_angle) + sprite->pl_pos.x,
			sprite->dist_pa * -sinf(sprite->angle
				- sprite->off_angle) + sprite->pl_pos.y);
	sprite->slice = ((HFOV * 2) / (float)W);
	sprite->off_angle = (x - (W * 0.5)) * sprite->slice;
	sprite->angle = atan2(mlx->player.anglesin, mlx->player.anglecos);
}

static void	draw_sprites_calc(t_mlx *mlx, int i, t_sprites *sprite)
{
	mlx->objects[mlx->objects[i].order].sprite_line =
		new_line(sprite->a, sprite->b);
	sprite->dist = get_dist(sprite->pl_pos, sprite->inter);
	if (sprite->dist == 0.0)
		sprite->dist = 0.01;
	sprite->line_height = (float)H / sprite->dist;
	sprite->draw_start = H * 0.5 - sprite->line_height * 0.5 +
		mlx->sectors[mlx->objects[mlx->objects[i].order].sector].floor;
	sprite->draw_end = sprite->draw_start + sprite->line_height;
	bot(i, mlx);
	sprite->curr_bmp = mlx->tab_bmp[
		mlx->objects[mlx->objects[i].order].tex];
}

void		draw_sprites(int x, t_mlx *mlx)
{
	int			i;
	t_sprites	sprite;

	i = -1;
	while (++i < NB_OBJ)
	{
		draw_sprites_precalc(x, mlx, i, &sprite);
		sprite.rel_dir.x = sprite.pl_pos.x +
			cos(sprite.angle + sprite.off_angle) * 50;
		sprite.rel_dir.y = sprite.pl_pos.y +
			sin(sprite.angle + sprite.off_angle) * 50;
		mlx->ray = new_line(sprite.pl_pos, sprite.rel_dir);
		sprite.inter = get_intersection(mlx->ray, new_line(sprite.a, sprite.b),
				get_slope(mlx->ray), get_slope(new_line(sprite.a, sprite.b)));
		if (!isinf(sprite.inter.x) && !isinf(sprite.inter.y) &&
				mlx->objects[mlx->objects[i].order].tex >= 0 \
				&& mlx->player.sector ==
				mlx->objects[mlx->objects[i].order].sector)
		{
			draw_sprites_calc(mlx, i, &sprite);
			vertical_sprite_lines(mlx, x, sprite, i);
		}
	}
}
