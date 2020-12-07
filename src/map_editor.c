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
	unsigned	sector;
	unsigned	vertex;
	float		dist;
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
			dist = get_dist_mouse_to_map(mlx->mouse_map, 
				mlx->sectors[sector].vertex[vertex]);
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
				!(mlx->sectors[sector].vertex[vertex].x == 
					mlx->sectors[mlx->editor.closest_sector].vertex[mlx->editor.closest_vertex].x &&
				mlx->sectors[sector].vertex[vertex].y == 
					mlx->sectors[mlx->editor.closest_sector].vertex[mlx->editor.closest_vertex].y))
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

void			draw_wall(t_mlx *mlx, int sector, int wall)
{
	int        color;

	mlx->editor.start.x = mlx->sectors[sector].vertex[wall].x *
		mlx->editor.sqr_size - mlx->editor.off_x;
	mlx->editor.start.y = mlx->sectors[sector].vertex[wall].y *
		mlx->editor.sqr_size - mlx->editor.off_y;

	if (wall != (int)mlx->sectors[sector].npoints - 1)
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
	color = TEAL;
	bresenham(mlx, color);
}

static void		draw_grid(t_mlx *mlx)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < mlx->editor.map_img_width * H - 1)
	{
		x = i / mlx->editor.map_img_width - mlx->editor.off_y;
		y = i % mlx->editor.map_img_width - mlx->editor.off_x;
		if ((x % mlx->editor.sqr_size == 0) && (y % mlx->editor.sqr_size == 0))
			mlx->editor.data_map[i] = 0xFFFFFF;
	}
}

static t_button		new_button(t_point orig, t_point end, int color)
{
	t_button	b;

	b.orig = orig;
	b.end = end;
	b.color = color;
	b.pressed = 0;
	b.toggled = 0;
	return (b);
}

int			check_button_pressed(t_mlx *mlx)
{
	int		button;

	button = -1;
	while (++button < NB_BUTTON)
	{
		if (is_inside(new_point(mlx->mouse.x - (3 * W) / 4, mlx->mouse.y), 
				mlx->editor.buttons[button]))
			return (button);
	}
	return (0);
}

void			init_buttons(t_mlx *mlx)
{
	int		y;
	int		height_button;
	int		i;

	y = 10;
	height_button = 50;
	i = 0;
	while (i < NB_BUTTON)
	{
		mlx->editor.buttons[i] = 
			new_button(new_point(10, y), new_point(W / 4 - 20, y + height_button), RED);
		y += height_button + 20;
		i += 1;
	}
}

void			toggle_button(t_mlx *mlx, int button)
{
	if (mlx->editor.buttons[button].toggled)
	{
		mlx->editor.buttons[button].toggled = 0;	
		mlx->editor.buttons[button].color = DEFAULT_BUTTON_COLOUR;
		mlx->editor.button_toggled = 0;
	}
	else if (!mlx->editor.button_toggled)
	{
		mlx->editor.buttons[button].toggled = 1;
		mlx->editor.buttons[button].color = PRESSED_BUTTON_COLOUR;
		mlx->editor.button_toggled = button;
	}
}

int			check_point_in_button(t_point p, t_mlx *mlx)
{
	int		button;

	button = -1;
	while (++button < NB_BUTTON)
	{
		if (is_inside(p, mlx->editor.buttons[button]))
			return (button);
	}
	return (0);
}

static void		draw_buttons(t_mlx *mlx)
{
	int		x;
	int		y;
	int		button;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < (W / 4))
		{
			if ((button = check_point_in_button(new_point(x, y), mlx)))
				mlx->editor.data_buttons[x + y * W / 4] = mlx->editor.buttons[button].color;
		}
	}
}

void			map_editor(t_mlx *mlx)
{
	unsigned	sector;
	unsigned	vertex;

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
	if (mlx->editor.buttons[BUTTON_ADD_SECTOR].toggled)
		draw_dashed_line_sector(mlx);
	else if (mlx->editor.buttons[BUTTON_MOD_VERTEX].toggled)
		ed_mod_vertex(mlx);
}
