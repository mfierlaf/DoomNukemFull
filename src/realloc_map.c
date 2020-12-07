#include "../include/doom_nukem.h"

int			copy_sector(t_sector dst, t_sector src)
{
	dst.brightness = src.brightness;
	dst.sky = src.sky;
	dst.floor = src.floor;
	dst.ceil = src.ceil;
	dst.vertex = malloc(sizeof(t_xy));
	dst.v_id = malloc(sizeof(int));
	dst.neighbors = malloc(sizeof(signed char));
	dst.npoints = src.npoints;
	return (1);
}

int		 	add_sector_to_map(t_mlx *mlx, t_sector sector)
{
	t_sector	*sectors;
	int		i;

	if (!(sectors = malloc(sizeof(t_sector) * mlx->num_sectors + 1)))
		return (-1);
	if (mlx->num_sectors >= NB_SECT_MAX)
		return (-2);
	i = -1;
	while (++i < mlx->num_sectors)
	{
		copy_sector(sectors[i], mlx->sectors[i]);
	}
//	mlx->num_sectors += 1;
//	copy_sector(sectors[i], sector);
//	free((mlx->sectors));
	mlx->sectors = sectors;
	return (1);
}
