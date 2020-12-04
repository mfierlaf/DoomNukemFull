/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void		read_object(int *i, char **split_line, t_mlx *mlx)
{
	t_pos pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	mlx->objects[*i].pos.x = atof(split_line[1]);
	mlx->objects[*i].pos.y = atof(split_line[2]);
	mlx->objects[*i].sector = ft_atoi(split_line[3]);
	mlx->objects[*i].tex = ft_atoi(split_line[4]);
	mlx->objects[*i].life = ft_atoi(split_line[5]);
	mlx->objects[*i].order = *i;
	mlx->objects[*i].distance = get_dist(pl_pos, mlx->objects[*i].pos);
	sprite_var(*i, mlx);
	++*i;
}

struct	xy		*read_map(char **split_line, t_mlx *mlx)
{
	int			num_vertices;
	struct xy	*vert;

	num_vertices = ft_atoi(split_line[1]);
	vert = malloc(num_vertices * sizeof(vert));
	mlx->vert_tex = malloc(num_vertices * sizeof(mlx->vert_tex));
	mlx->num_sectors = ft_atoi(split_line[2]);
	mlx->sectors = malloc(mlx->num_sectors * sizeof(*mlx->sectors));
	return (vert);
}

struct	xy		*read_vertices(int *j, struct xy *vert,
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

static int		read_decos(int i, char **split_line, t_mlx *mlx)
{
	mlx->decos[i].sector = atof(split_line[1]);
	mlx->decos[i].wall = atof(split_line[2]);
	mlx->decos[i].tex = ft_atoi(split_line[3]);
	return (i++);
}

int				read_sector(int *k, struct xy *vert,
	char **split_line, t_mlx *mlx)
{
	int			vertex_len;
	int			n;

	vertex_len = 0;
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
	while (split_line[vertex_len] != NULL)
		vertex_len++;
	vertex_len -= 4;
	mlx->sectors[*k].npoints = vertex_len / 2;
	vertex_len /= 2;
	mlx->sectors[*k].neighbors = malloc((vertex_len) * \
		sizeof(*mlx->sectors[*k].neighbors));
	mlx->sectors[*k].vertex = malloc((vertex_len + 1) * \
		sizeof(*mlx->sectors[*k].vertex));
	mlx->sectors[*k].vert_id = malloc((vertex_len + 1) * \
		sizeof(*mlx->sectors[*k].vert_id));
	n = -1;
	while (++n < vertex_len)
		mlx->sectors[*k].neighbors[n] = ft_atoi(split_line[vertex_len + n + 4]);
	n = -1;
	while (++n < vertex_len)
	{
		mlx->sectors[*k].vertex[n + 1] = vert[ft_atoi(split_line[n + 4])];
		mlx->sectors[*k].vert_id[n + 1] = ft_atoi(split_line[n + 4]);
	}
	mlx->sectors[*k].vertex[0] = mlx->sectors[*k].vertex[vertex_len];
	mlx->sectors[*k].vert_id[0] = mlx->sectors[*k].vert_id[vertex_len];
	return (n);
}

void			read_player(int n, char **split_line, t_mlx *mlx)
{
	float		angle;
	struct xy	v;

	v.x = ft_atoi(split_line[1]);
	v.y = ft_atoi(split_line[2]);
	angle = ft_atoi(split_line[3]);
	n = ft_atoi(split_line[4]);
	mlx->player = (struct s_player) {
		{v.x, v.y, 0}, {0, 0, 0}, angle, 0, 0, 0, n,
		100, 0, {0, 0, 0}, {0, 0, 0}};
	mlx->player.where.z = mlx->sectors[mlx->player.sector].floor + EyeHeight;
}

void			load_data(t_mlx *mlx)
{
	int			fd;
	char		*line;
	char		**split_line;
	struct xy	*vert;
	int			n;
	int			j;
	int			k;
	int			i;
	int			l;

	j = 0;
	k = -1;
	i = 1;
	l = 0;
	if ((fd = open("./map-clear.txt", O_RDONLY)) < 0)
		kill_mlx("ERROR IN MAP\n", mlx);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(split_line = ft_strsplit(line, ' ')))
			kill_mlx("ERROR IN MAP\n", mlx);
		if (split_line[0][0] == 'm')
			vert = read_map(split_line, mlx);
		else if (split_line[0][0] == 'v')
			vert = read_vertices(&j, vert, split_line, mlx);
		else if (split_line[0][0] == 's')
			n = read_sector(&k, vert, split_line, mlx);
		else if (split_line[0][0] == 'o')
			read_object(&i, split_line, mlx);
		else if (split_line[0][0] == 'd')
			l = read_decos(l, split_line, mlx);
		else if (split_line[0][0] == 'p')
			read_player(n, split_line, mlx);
	}
	close(fd);
	free(vert);
	free(line);
}

void			unload_data(t_mlx *mlx)
{
	unsigned	a;

	a = -1;
	while (++a < mlx->num_sectors)
		free(mlx->sectors[a].vertex);
	a = -1;
	while (++a < mlx->num_sectors)
		free(mlx->sectors[a].neighbors);
	free(mlx->sectors);
	mlx->sectors = NULL;
	mlx->num_sectors = 0;
}
