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

static void	read_object(int *i, char **split_line, t_mlx *mlx)
{
	t_pos	pl_pos;

	pl_pos.x = mlx->player.where.x;
	pl_pos.y = mlx->player.where.y;
	mlx->objects[*i].pos.x = ft_atof(split_line[1]);
	mlx->objects[*i].pos.y = ft_atof(split_line[2]);
	mlx->objects[*i].sector = ft_atoi(split_line[3]);
	mlx->objects[*i].tex = ft_atoi(split_line[4]);
	mlx->objects[*i].life = ft_atoi(split_line[5]);
	mlx->objects[*i].order = *i;
	mlx->objects[*i].distance = get_dist(pl_pos, mlx->objects[*i].pos);
	sprite_var(*i, mlx);
	++*i;
}

static int	read_decos(int i, char **split_line, t_mlx *mlx)
{
	mlx->decos[i].sector = ft_atof(split_line[1]);
	mlx->decos[i].wall = ft_atof(split_line[2]);
	mlx->decos[i].tex = ft_atoi(split_line[3]);
	return (i++);
}

t_load		init_load(void)
{
	t_load	load;

	load.j = 0;
	load.k = -1;
	load.i = 1;
	load.l = 0;
	return (load);
}

void		free_lines(t_load *load)
{
	int		i;

	i = 0;
	free(load->line);
	while (load->split_line[i])
	{
		free(load->split_line[i]);
		i++;
	}
	free(load->split_line);
}

void		load_data(t_mlx *mlx)
{
	t_load	load;

	load = init_load();
	if ((load.fd = open("./map-clear.txt", O_RDONLY)) < 0)
		kill_mlx("ERROR IN MAP\n", mlx);
	while (get_next_line(load.fd, &load.line) > 0)
	{
		if (!(load.split_line = ft_strsplit(load.line, ' ')))
			kill_mlx("ERROR IN MAP\n", mlx);
		if (load.split_line[0][0] == 'm')
			load.vert = read_map(load.split_line, mlx);
		else if (load.split_line[0][0] == 'v')
			load.vert = read_vertices(&load.j, load.vert, load.split_line, mlx);
		else if (load.split_line[0][0] == 's')
			load.n = read_sector(&load.k, load.vert, load.split_line, mlx);
		else if (load.split_line[0][0] == 'o')
			read_object(&load.i, load.split_line, mlx);
		else if (load.split_line[0][0] == 'd')
			load.l = read_decos(load.l, load.split_line, mlx);
		else if (load.split_line[0][0] == 'p')
			read_player(load.n, load.split_line, mlx);
		free_lines(&load);
	}
	close(load.fd);
	free(load.vert);
}

void		unload_data(t_mlx *mlx)
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
