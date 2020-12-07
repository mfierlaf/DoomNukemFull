/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static	int		kill_mlx_cross(t_mlx *mlx)
{
	system("pkill afplay");
	if (mlx != NULL)
		unload_data(mlx);
	mlx = NULL;
	exit(1);
	return (0);
}

static void		init_mlx(t_mlx *mlx)
{
	if (!(mlx->win = mlx_new_window(mlx->mlx, W, H, "DOOM")))
		kill_mlx("mlx_new_window fail\n", mlx);
	if (!(mlx->img = mlx_new_image(mlx->mlx, W, H)))
		kill_mlx("mlx_new_image fail\n", mlx);
	if (!(mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl,
		&mlx->endian)))
		kill_mlx("mlx_get_data_addr fail\n", mlx);
	if (!(mlx->editor.img = mlx_new_image(mlx->mlx, ((3 * W) / 4), H)))
		kill_mlx("mlx_new_image fail\n", mlx);
	if (!(mlx->editor.data = (int *)mlx_get_data_addr(mlx->editor.img,
		&mlx->editor.bpp, &mlx->editor.sl, &mlx->editor.endian)))
		kill_mlx("editor_get_data_addr fail\n", mlx);
}

int				main(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		kill_mlx("mlx_init fail\n", mlx);
	if (!(mlx->mlx = mlx_init()))
		kill_mlx("mlx_init fail\n", mlx);
	init(mlx);
	load_data(mlx);
	init_mlx(mlx);
	load_texture(mlx);
	mlx_hook(mlx->win, BUTTONPRESS, (1L << 2), button_mouse, mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, (1L << 6), mouse_hook, mlx);
	mlx_hook(mlx->win, KP, (1L << 0), ft_key_hook, mlx);
	mlx_hook(mlx->win, KEYRELEASE, (1L << 1), stop_movement, mlx);
	mlx_hook(mlx->win, DESTROYNOTIFY, (1L << 17), kill_mlx_cross, mlx);
	music(mlx);
	mlx_loop_hook(mlx->mlx, expose, mlx);
	mlx_loop(mlx->mlx);
	unload_data(mlx);
	return (0);
}
