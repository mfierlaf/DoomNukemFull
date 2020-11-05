#include "../include/doom_nukem.h"

static void	draw_grid(t_mlx *mlx)
{
	int i;
	int x;
	int y;

	i = -1;
	while (++i < mlx->editor.map_img_width * H - 1)
	{
		x = i / mlx->editor.map_img_width;
		y = i % mlx->editor.map_img_width;
		if ((x % 25 == 0) && (y % 25 == 0))
			mlx->editor.data[i] = 0xFFFFFF;
	}
}
void		map_editor(t_mlx *mlx)
{
	draw_grid(mlx);
}