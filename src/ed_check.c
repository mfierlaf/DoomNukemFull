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
			if (sect[i_vertex].x == sect[i_iterator].x && 
				sect[i_vertex].y == sect[i_iterator].y)
				return (0);
		}
	}
	return (1);
}

static int	ed_check_if_is_line(t_sector sect)
{
	int	
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


