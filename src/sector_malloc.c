/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-duf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 10:29:05 by cvan-duf          #+#    #+#             */
/*   Updated: 2019/06/18 17:25:14 by cvan-duf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

void			sector_malloc(t_mlx *mlx, int v_l, int *k)
{
	if (!(mlx->sectors[*k].neighbors = malloc((v_l) *
		sizeof(*mlx->sectors[*k].neighbors))))
		kill_mlx("sectors_neighbor malloc fail\n", mlx);
	if (!(mlx->sectors[*k].vertex = malloc((v_l + 1) *
		sizeof(*mlx->sectors[*k].vertex))))
		kill_mlx("sectors_vertex malloc fail\n", mlx);
	if (!(mlx->sectors[*k].v_id = malloc((v_l + 1) *
		sizeof(*mlx->sectors[*k].v_id))))
		kill_mlx("sectors_v_id malloc fail\n", mlx);
}
