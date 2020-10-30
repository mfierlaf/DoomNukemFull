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

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void vline(int x, int y1, int y2, int top, int middle, int bottom, t_mlx *mlx)
{
  int y;

  y = y1;
  y1 = clamp(y1, 0, H - 1);
  y2 = clamp(y2, 0, H - 1);
  if (y2 == y1)
		mlx->data[y1 * W + x] = middle;
  else if (y2 > y1)
  {
    mlx->data[y1 * W + x] = top;
    while (++y < y2)
    {
      mlx->data[y * W + x] = middle;
    }
    mlx->data[y2 * W + x] = bottom;
  }
}


struct Scaler Scaler_Init(int a, int b, int c, int d, int f)
{
  struct Scaler scaler;

  scaler.result = d + (b-1 - a) * (f-d) / (c-a);
  scaler.bop = ((f<d) ^ (c<a)) ? -1 : 1;
  scaler.fd = abs(f-d);
  scaler.ca = abs(c-a); 
  scaler.cache = (int)((b-1-a) * abs(f-d)) % abs(c-a);
  return (scaler);
}

// Scaler_Next: Return (b++ - a) * (f-d) / (c-a) + d using the initial values passed to Scaler_Init().
int Scaler_Next(struct Scaler *i)
{
    for (i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca)
      i->result += i->bop;
    return i->result;
}


// void vline2(int x, int y1, int y2, struct Scaler ty /*scaler_init*/, unsigned txtx, t_mlx *mlx)
// {
//     y1 = clamp(y1, 0, H - 1);
//     y2 = clamp(y2, 0, H - 1);
//     for (int y = y1; y <= y2; ++y)
//     {
//         mlx->txty = Scaler_Next(&ty);
//         mlx->data[y * W + x] = mlx->tex[1].data[(mlx->txty % TEXTURE_SIZE) * TEXTURE_SIZE + (txtx % TEXTURE_SIZE)];
//     }
// }

void        vertical_line(int x, int y1, int y2, struct Scaler ty /*scaler_init*/, unsigned txtx, t_mlx *mlx)
{
    int color;

    y1 = clamp(y1, 0, H - 1);
    y2 = clamp(y2, 0, H - 1);
    for (int y = y1; y <= y2; ++y)
    {
      mlx->txty = Scaler_Next(&ty);
      color = get_color(mlx->tab_bmp[0], (txtx % TEXTURE_SIZE), (mlx->txty % TEXTURE_SIZE));
      if (color != FILTER_COLOR)
        mlx->data[y * W + x] = color;
    }
}

