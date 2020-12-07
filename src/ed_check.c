#include "../include/doom_nukem.h"

static int	ed_check_sector_integrity(t_sector sect)
{
	int	i_vertex;
	int	i_iterator;

	i_vertex = -1;
	while (++i_vertex < sect.npoints - 1)
	{
		i_iterator = i_vertex;
		while (++i_iterator < sect.npoints)
		{
			if (sect.vertex[i_vertex].x == sect.vertex[i_iterator].x && 
				sect.vertex[i_vertex].y == sect.vertex[i_iterator].y)
				return (0);
		}
	}
	return (1);
}

static int	ed_check_if_is_line(t_sector sect)
{
	int	i_vertex;
	float	slope;

	i_vertex = 0;
	if (sect.npoints <= 3)
		return (1);
	slope = get_slope(new_line(
			new_pos(sect.vertex[sect.npoints - 1].x, sect.vertex[sect.npoints - 1].y),
			new_pos(sect.vertex[i_vertex].x, sect.vertex[i_vertex].y)));
	while (i_vertex < sect.npoints - 1)
	{
		if (slope != get_slope(new_line(
			new_pos(sect.vertex[i_vertex].x, sect.vertex[i_vertex].y),
			new_pos(sect.vertex[i_vertex + 1].x, sect.vertex[i_vertex].y))))
			return (0);
		i_vertex++;
	}
	return (1);
}

int		ed_check_can_add(t_mlx *mlx, t_sector sect)
{
	int	i_vertex;

	i_vertex = -1;
	if (mlx->num_sectors + 1 >= NB_SECT_MAX)
		return (0);
	ed_check_sector_integrity(sect);
	return (1);
}

