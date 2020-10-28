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
void vline(int x, int y1,int y2, int top, int middle, int bottom, t_mlx *mlx)
{
  int y;

  y = y1;
  y1 = clamp(y1, 0, H-1);
  y2 = clamp(y2, 0, H-1);
  if(y2 == y1)
		mlx->data[y1*W+x] = middle;
  else if(y2 > y1)
  {
    mlx->data[y1*W+x] = top;
    while (++y<y2)
    {
      mlx->data[y*W+x] = middle;
    }
    mlx->data[y2*W+x] = bottom;
  }
}
