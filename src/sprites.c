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

void                vertical_sprite_lines(t_mlx *mlx, int x, t_pos sp_orig,
    t_pos sp_end, int draw_start, int draw_end, t_pos inter, t_bmp *curr_bmp)
{
    int             y;
    int             y_max;
    float           line_h;
    float           dx;
    float           dy;
    float           rel_x;
    float           rel_y;
    int             color;

    y = draw_start;
    y_max = draw_end;
    if (draw_start < 0)
        y = 0;
    if (draw_end > W)
        y_max = W;
    line_h = draw_end - draw_start;
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
                // if (color != FILTER_COLOR)
                    mlx->data[x + y * W] = color;
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
        sp_pos = new_pos(mlx->objects[i].pos.x, mlx->objects[i].pos.y);
        pl_pos = new_pos(mlx->player.where.x, mlx->player.where.y);
        dist_ps = get_dist(pl_pos, sp_pos);
        angle = get_angle(pl_pos, sp_pos);
        dist_pa = sqrtf(dist_ps * dist_ps + 0.5 * 0.5);
        off_angle = atanf(0.5 / dist_ps);
        a = new_pos(dist_pa * cosf(angle + off_angle) + pl_pos.x,
            dist_pa * -sinf(angle + off_angle) + pl_pos.y);
        b = new_pos(dist_pa * cosf(angle - off_angle) + pl_pos.x,
            dist_pa * -sinf(angle - off_angle) + pl_pos.y);
        mlx->objects[i].sprite_line = new_line(a, b);
        // float slice = M_PI / (3.0 * (float)W);
        float slice = ((HFOV * 2) / (float)W);
        off_angle = (x - (W * 0.5)) * slice;
        // anglesin = dir.y anglecos = dir.x
        // angle = atan2(mlx->player.dir.y, mlx->player.dir.x);
        angle = atan2(mlx->player.anglesin, mlx->player.anglecos);
        t_pos rel_dir;
        rel_dir.x = pl_pos.x + cos(angle + off_angle) * 50;
        rel_dir.y = pl_pos.y + sin(angle + off_angle) * 50;


        // float vxa;
        // float vxb;
        // float vya;
        // float vyb;
        // float txa;
        // float tya;
        // float txb;
        // float tyb;
    
        // vxa = a.x - mlx->player.where.x;
        // vya = a.y - mlx->player.where.y;
        // vxb = b.x - mlx->player.where.x;
        // vyb = b.y - mlx->player.where.y;
        // txa = vxa * mlx->player.anglesin - vya * mlx->player.anglecos;
        // tya = vxa * mlx->player.anglecos + vya * mlx->player.anglesin;
        // txb = vxb * mlx->player.anglesin - vyb * mlx->player.anglecos;
        // tyb = vxb * mlx->player.anglecos + vyb * mlx->player.anglesin;

        mlx->ray = new_line(pl_pos, rel_dir);
        inter = get_intersection(mlx->ray, new_line(a, b),
            get_slope(mlx->ray), get_slope(new_line(a, b)));


        // float vx = inter.x - mlx->player.where.x;
        // float vy = inter.y - mlx->player.where.y;
        // float xscale = (W * HFOV) / (vx * mlx->player.anglecos + vy * mlx->player.anglesin);
        // float yscale = (H * VFOV) / (inter.y) / 200;


        if (!isinf(inter.x) && !isinf(inter.y) && mlx->objects[i].tex >= 0) // && mlx->player.sector == mlx->objects[i].sector)
        {
            dist = get_dist(pl_pos, inter);
            if (dist == 0.0)
                dist = 0.01;
            line_height = (float)H / dist;
            draw_start = H * 0.5 - line_height * 0.5 - mlx->mouse.y + mlx->sectors[mlx->objects[i].sector].floor;
            draw_end = draw_start + line_height;
            // if (wall_dist > dist)
            bot(i, mlx);
            vertical_sprite_lines(mlx, x, a, b, draw_start, draw_end,
                                inter, mlx->tab_bmp[mlx->objects[i].tex]);
            // unsigned txtx = rtx + mlx->player.where.x * 16;
            // vertical_line(x, draw_end, draw_start, (struct Scaler)Scaler_init(a.y, draw_end, b.y, 0, TEXTURE_SIZE - 1), txtx, mlx);
        }
    }
}
