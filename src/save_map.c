#include "../include/doom_nukem.h"

int 	is_vertex(t_mlx *mlx, int i)
{
	if (i != mlx->editor.map_img_width * H - 1)
		if (mlx->editor.data_map[i + 1] == 0xFF0000)
			return (1);
	if (i <= ((mlx->editor.map_img_width * H - 1) - H))
		if (mlx->editor.data_map[i + H] == 0xFF0000)
			return (1);
	if (i != 0)
		if (mlx->editor.data_map[i - 1] == 0xFF0000)
			return (1);
	if (i >=  H)
		if (mlx->editor.data_map[i - H] == 0xFF0000)
			return (1);
	return (0);
}

