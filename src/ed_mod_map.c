#include "../include/doom_nukem.h"

int		ed_auth_move_vertex(t_mlx *mlx)
{
	int	i;
	int	j;
	int	moving;

	i = -1;
	moving = 0;
	while (++i < mlx->num_sectors)
	{
		j = -1;
		while (++j < mlx->sectors[i].npoints)
		{
			if ((int)mlx->mouse_map.x == mlx->sectors[i].vertex[j].x &&
				(int)mlx->mouse_map.y == mlx->sectors[i].vertex[j].y)
			{
				moving = 1;
				mlx->sectors[i].vertex[j].to_be_moved = 1;
			}
		}
	}
	return (moving);
}

void		ed_mod_vertex(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	if (mlx->editor.moving_vertex)
	{
		while (++i < mlx->num_sectors)
		{
			j = -1;
			while (++j < mlx->sectors[i].npoints)
			{
				if (mlx->sectors[i].vertex[j].to_be_moved)
				{
					mlx->sectors[i].vertex[j].x = mlx->mouse_map.x;
					mlx->sectors[i].vertex[j].y = mlx->mouse_map.y;
				}
			}
		}

	}	
}

void		ed_reset_to_be_moved(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	if (mlx->editor.moving_vertex)
	{
		while (++i < mlx->num_sectors)
		{
			j = -1;
			while (++j < mlx->sectors[i].npoints)
			{
				if (mlx->sectors[i].vertex[j].to_be_moved)
				{
					mlx->sectors[i].vertex[j].to_be_moved = 0;
				}
			}		
		}
	}
}
