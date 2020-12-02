/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void                multi_sprites(int sprite, t_mlx *mlx)
{
    float               angle;
    t_pos               pl_pos;

    pl_pos.x = mlx->player.where.x;
    pl_pos.y = mlx->player.where.y;
    angle = get_angle(mlx->objects[mlx->objects[sprite].order].pos,
                pl_pos);
    if (angle >= -M_PI / 8 && angle < M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_1;
    if (angle >= M_PI / 8 && angle < 3 * M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_2;
    if (angle >= 3 * M_PI / 8 && angle < 5 * M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_3;
    if (angle >= 5 * M_PI / 8 && angle < 7 * M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_4;
    if (angle >= 7 * M_PI / 8 && angle < -7 * M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_5;
    if (angle >= -7 * M_PI / 8 && angle < -5 * M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_6;
    if (angle >= -5 * M_PI / 8 && angle < -3 * M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_7;
    if (angle >= -3 * M_PI / 8 && angle < -M_PI / 8)
        mlx->objects[mlx->objects[sprite].order].tex = MULTI_8;
}

int             double_swap(t_mlx *mlx, int i, int j)
{
    ft_swap_float(&(mlx->objects[i].distance), &(mlx->objects[j].distance));
    ft_swap_int(&(mlx->objects[i].order), &(mlx->objects[j].order));
    return (1);
}

void            sort_sprites(t_mlx *mlx)
{
    int             gap;
    int             swapped;
    int             i;
    int             j;

    swapped = 0;
    gap = NB_OBJ;
    while (gap > 1 || swapped)
    {
        swapped = 0;
        gap = (gap * 10) / 13;
        if (gap == 9 || gap == 10)
            gap = 11;
        else if (gap < 1)
            gap = 1;
        i = 1;
        while (i < NB_OBJ - gap)
        {
            j = i + gap;
            if (mlx->objects[i].distance < mlx->objects[j].distance)
                swapped = double_swap(mlx, i, j);
            i++;
        }
    }
}

void                vertical_sprite_lines(t_mlx *mlx, int x, t_pos sp_orig,
    t_pos sp_end, int draw_start, int draw_end, t_pos inter, t_bmp *curr_bmp, int i)
{
    int             y;
    int             y_max;
    float           dx;
    float           dy;
    float           rel_x;
    float           rel_y;
    int             color;

    draw_start = clamp(draw_start, 0, H - 1) - mlx->mouse.y;
    draw_end = clamp(draw_end, 0, H - 1) - mlx->mouse.y;
    y = draw_start;
    y_max = draw_end;
    while (y < y_max)
    {
        if (dx != 0)
            dx = (inter.x - sp_orig.x) / (sp_end.x - sp_orig.x);
        else
            dx = (inter.y - sp_orig.y) / (sp_end.y - sp_orig.y);
        if (!isnan(dx) && !isnan(dy))
        {
            rel_x = dx * curr_bmp->header.width_px;
            dy = (float)(y - draw_start) / (float)(draw_end - draw_start);
            rel_y = dy * curr_bmp->header.height_px;
            if (valid_pixel(x, y))
            {
                color = get_color(curr_bmp, (int)rel_x, (int)rel_y);
                if (color != FILTER_COLOR)
                {
                    if (mlx->sectors[mlx->objects[mlx->objects[i].order].sector].brightness == 0)
                        color = (color >> 1) & 8355711;
                    mlx->data[x + y * W] = color;
                }
            }
        }
        y++;
    }
}

void draw_sprites(int x, t_mlx *mlx)
{
    int i;
    t_pos   pl_pos;
    t_pos           a;
    t_pos           sp_pos;
    t_pos           b;
    float           dist_ps;
    float           dist_pa;
    t_pos           inter;
    int             draw_start;
    int             draw_end;
    int             line_height;
    float           dist;
    float           angle;
    float           off_angle;

    i = -1;
    while (++i < NB_OBJ)
    {
        if (mlx->objects[mlx->objects[i].order].tex >= MULTI_1 && mlx->objects[mlx->objects[i].order].tex <= MULTI_8)
            multi_sprites(i, mlx);
        sp_pos = new_pos(mlx->objects[mlx->objects[i].order].pos.x, mlx->objects[mlx->objects[i].order].pos.y);
        pl_pos = new_pos(mlx->player.where.x, mlx->player.where.y);
        dist_ps = get_dist(pl_pos, sp_pos);
        angle = get_angle(pl_pos, sp_pos);
        if (dist_ps < 1.0)
            dist_ps = 1.0;
        dist_pa = sqrtf(dist_ps * dist_ps + 0.5 * 0.5);
        off_angle = atanf(0.5 / dist_ps);
        a = new_pos(dist_pa * cosf(angle + off_angle) + pl_pos.x,
            dist_pa * -sinf(angle + off_angle) + pl_pos.y);
        b = new_pos(dist_pa * cosf(angle - off_angle) + pl_pos.x,
            dist_pa * -sinf(angle - off_angle) + pl_pos.y);
        float slice = ((HFOV * 2) / (float)W);
        off_angle = (x - (W * 0.5)) * slice;
        angle = atan2(mlx->player.anglesin, mlx->player.anglecos);
        t_pos rel_dir;
        rel_dir.x = pl_pos.x + cos(angle + off_angle) * 50;
        rel_dir.y = pl_pos.y + sin(angle + off_angle) * 50;
        mlx->ray = new_line(pl_pos, rel_dir);
        inter = get_intersection(mlx->ray, new_line(a, b),
            get_slope(mlx->ray), get_slope(new_line(a, b)));
        if (!isinf(inter.x) && !isinf(inter.y) && mlx->objects[mlx->objects[i].order].tex >= 0) // && mlx->player.sector == mlx->objects[mlx->objects[i].order].sector)
        {
            mlx->objects[mlx->objects[i].order].sprite_line = new_line(a, b);
            dist = get_dist(pl_pos, inter);
            if (dist == 0.0)
                dist = 0.01;
            line_height = (float)H / dist;
            draw_start = H * 0.5 - line_height * 0.5 + mlx->sectors[mlx->objects[mlx->objects[i].order].sector].floor;
            draw_end = draw_start + line_height;
            bot(i, mlx);
            vertical_sprite_lines(mlx, x, a, b, draw_start, draw_end,
                                inter, mlx->tab_bmp[mlx->objects[mlx->objects[i].order].tex], i);
        }
    }
}
