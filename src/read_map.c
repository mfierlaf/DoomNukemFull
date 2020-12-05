/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

t_xy		*read_map(char **split_line, t_mlx *mlx)
{
	int		num_vertices;
	t_xy	*vert;

	num_vertices = ft_atoi(split_line[1]);
	vert = malloc(num_vertices * sizeof(vert));
	mlx->vert_tex = malloc(num_vertices * sizeof(mlx->vert_tex));
	mlx->num_sectors = ft_atoi(split_line[2]);
	mlx->sectors = malloc(mlx->num_sectors * sizeof(*mlx->sectors));
	return (vert);
}

t_xy		*read_vertices(int *j, t_xy *vert,
	char **split_line, t_mlx *mlx)
{
	int			i;

	i = 2;
	while (split_line[i])
	{
		mlx->vert_tex[*j] = ft_atoi(split_line[i + 1]);
		vert[*j].y = atof(split_line[1]);
		vert[*j].x = atof(split_line[i]);
		++*j;
		i += 2;
	}
	return (vert);
}

static int	sector_malloc(int *k, t_xy *vert, char **split_line, t_mlx *mlx)
{
	int		v_l;
	int		n;

	v_l = 0;
	while (split_line[v_l] != NULL)
		v_l++;
	mlx->sectors[*k].npoints = (v_l - 4) / 2;
	v_l = (v_l - 4) / 2;
	mlx->sectors[*k].neighbors = malloc((v_l) *\
		sizeof(*mlx->sectors[*k].neighbors));
	mlx->sectors[*k].vertex = malloc((v_l + 1) *\
		sizeof(*mlx->sectors[*k].vertex));
	mlx->sectors[*k].v_id = malloc((v_l + 1) * sizeof(*mlx->sectors[*k].v_id));
	n = -1;
	while (++n < v_l)
		mlx->sectors[*k].neighbors[n] = ft_atoi(split_line[v_l + n + 4]);
	n = -1;
	while (++n < v_l)
	{
		mlx->sectors[*k].vertex[n + 1] = vert[ft_atoi(split_line[n + 4])];
		mlx->sectors[*k].v_id[n + 1] = ft_atoi(split_line[n + 4]);
	}
	mlx->sectors[*k].vertex[0] = mlx->sectors[*k].vertex[v_l];
	mlx->sectors[*k].v_id[0] = mlx->sectors[*k].v_id[v_l];
	return (n);
}

int			read_sector(int *k, t_xy *vert, char **split_line, t_mlx *mlx)
{
	int		n;

	++*k;
	mlx->sectors[*k].floor = atof(split_line[1]);
	mlx->sectors[*k].ceil = atof(split_line[2]);
	mlx->sectors[*k].brightness = ft_atoi(split_line[3]);
	if (mlx->sectors[*k].ceil < 0)
	{
		mlx->sectors[*k].ceil = -mlx->sectors[*k].ceil;
		mlx->sectors[*k].sky = 1;
	}
	else
		mlx->sectors[*k].sky = 0;
	n = sector_malloc(k, vert, split_line, mlx);
	return (n);
}

void		read_player(int n, char **split_line, t_mlx *mlx)
{
	float	angle;
	t_xy	v;

	v.x = ft_atoi(split_line[1]);
	v.y = ft_atoi(split_line[2]);
	angle = ft_atoi(split_line[3]);
	n = ft_atoi(split_line[4]);
	mlx->player = (struct s_player) {
		{v.x, v.y, 0}, {0, 0, 0}, angle, 0, 0, 0, n,
		100, 0, {0, 0, 0}, {0, 0, 0}};
	mlx->player.where.z = mlx->sectors[mlx->player.sector].floor + EYEHEIGHT;
}
