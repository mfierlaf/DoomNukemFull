#include "../include/doom_nukem.h"

void			draw_dashed_wall(t_mlx *mlx, int sector, int wall, int color)
{
	mlx->editor.start.x = mlx->mouse_map.x *
		mlx->editor.sqr_size - mlx->editor.off_x;
	mlx->editor.start.y = mlx->mouse_map.y *
		mlx->editor.sqr_size - mlx->editor.off_y;
	mlx->editor.end.x = mlx->sectors[sector].vertex[wall].x *
			mlx->editor.sqr_size - mlx->editor.off_x;
	mlx->editor.end.y = mlx->sectors[sector].vertex[wall].y *
			mlx->editor.sqr_size - mlx->editor.off_y;
	mlx->editor.start.x *= -1;
	mlx->editor.start.y *= -1;
	mlx->editor.end.x *= -1;
	mlx->editor.end.y *= -1;
	dashed_bresenham(mlx, color);
}

void			draw_dashed_line_sector(t_mlx *mlx)
{
	int			sector;
	int			vertex;
	float		dist;
	float		dist2;
	float		closest_dist;
	float		closest_dist2;

	sector = 0;
	mlx->editor.closest_vertex = 0;
	mlx->editor.closest_sector = 0;
	closest_dist = get_dist_mouse_to_map(mlx->mouse_map, mlx->sectors[0].vertex[0]);
	while (sector < mlx->num_sectors)
	{
		vertex = 0;
		while (vertex < mlx->sectors[sector].npoints)
		{
			dist = get_dist_mouse_to_map(mlx->mouse_map, mlx->sectors[sector].vertex[vertex]);
			if (dist <= closest_dist)
			{
				closest_dist = dist;
				mlx->editor.closest_sector = sector;
				mlx->editor.closest_vertex = vertex;
			}
			vertex++;
		}
		sector++;
	}
	mlx->editor.closest_sector2 = 0;
	mlx->editor.closest_vertex2 = 0;
	sector = 0;
	closest_dist2 = get_dist_mouse_to_map(mlx->mouse_map, mlx->sectors[0].vertex[1]);
	dist = closest_dist2;
	while (sector < mlx->num_sectors)
	{
		vertex = 0;
		while (vertex < mlx->sectors[sector].npoints)
		{
			dist = get_dist_mouse_to_map(mlx->mouse_map, mlx->sectors[sector].vertex[vertex]);
			if (dist <= closest_dist2 &&
				!(mlx->sectors[sector].vertex[vertex].x == mlx->sectors[mlx->editor.closest_sector].vertex[mlx->editor.closest_vertex].x &&
				mlx->sectors[sector].vertex[vertex].y == mlx->sectors[mlx->editor.closest_sector].vertex[mlx->editor.closest_vertex].y))
			{
				closest_dist2 = dist;
				mlx->editor.closest_sector2 = sector;
				mlx->editor.closest_vertex2 = vertex;
			}
			vertex++;
		}
		sector++;
	}

	draw_dashed_wall(mlx, mlx->editor.closest_sector, mlx->editor.closest_vertex, APPLE);
	draw_dashed_wall(mlx, mlx->editor.closest_sector2, mlx->editor.closest_vertex2, RED);
}

void        draw_wall(t_mlx *mlx, int sector, int wall)
{
	int        color;

	mlx->editor.start.x = mlx->sectors[sector].vertex[wall].x *
		mlx->editor.sqr_size - mlx->editor.off_x;
	mlx->editor.start.y = mlx->sectors[sector].vertex[wall].y *
		mlx->editor.sqr_size - mlx->editor.off_y;

	if (wall != mlx->sectors[sector].npoints - 1)
	{
		mlx->editor.end.x = mlx->sectors[sector].vertex[wall + 1].x *
			mlx->editor.sqr_size - mlx->editor.off_x;
		mlx->editor.end.y = mlx->sectors[sector].vertex[wall + 1].y *
			mlx->editor.sqr_size - mlx->editor.off_y;
	}
	else
	{
		mlx->editor.end.x = mlx->sectors[sector].vertex[0].x *
			mlx->editor.sqr_size - mlx->editor.off_x;
		mlx->editor.end.y = mlx->sectors[sector].vertex[0].y *
			mlx->editor.sqr_size - mlx->editor.off_y;
	}
	mlx->editor.start.x *= -1;
	mlx->editor.start.y *= -1;
	mlx->editor.end.x *= -1;
	mlx->editor.end.y *= -1;
	// if (mlx->sectors[sector].vertex[wall].is_portal)
	// 	color = GREY;
//	if (wall == 0)
//		color = WHITE;
//	else if (wall == 1)
//		color = RED;
//	else if (wall == 2)
//		color = GREEN;
//	else if (wall == 3)
//		color = ORANGE;
//	else if (wall == 4)
	//	color = BLUE;
	// else if (mlx->sectors[sector].vertex[wall].tex == 5)
	// 	color = LIGHT_BLUE;
	// else if (mlx->sectors[sector].vertex[wall].tex == 6)
	// 	color = PINK;
	// else if (mlx->sectors[sector].vertex[wall].tex == 7)
	// 	color = PURPLE;
	// else if (mlx->sectors[sector].vertex[wall].tex == 8)
	 	color = TEAL;
	// else if (mlx->sectors[sector].vertex[wall].tex == 9)
	//color = APPLE;
	bresenham(mlx, color);
}

static void	draw_grid(t_mlx *mlx)
{
	int i;
	int x;
	int y;

	i = -1;
	while (++i < mlx->editor.map_img_width * H - 1)
	{
		x = i / mlx->editor.map_img_width - mlx->editor.off_y;
		y = i % mlx->editor.map_img_width - mlx->editor.off_x;
		if ((x % mlx->editor.sqr_size == 0) && (y % mlx->editor.sqr_size == 0))
			mlx->editor.data_map[i] = 0xFFFFFF;
	}
}

static void	draw_buttons(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < (W / 4) * H)
	{
		
	}
}

void		map_editor(t_mlx *mlx)
{
	int sector;
	int vertex;

	sector = 0;
	draw_grid(mlx);
	draw_buttons(mlx);
	while (sector < mlx->num_sectors)
	{
		vertex = 0;
		while (vertex < mlx->sectors[sector].npoints)
		{
			draw_wall(mlx, sector, vertex);
			vertex++;
		}
		sector++;
	}
	if (mlx->events.new_sector)
		draw_dashed_line_sector(mlx);
}
