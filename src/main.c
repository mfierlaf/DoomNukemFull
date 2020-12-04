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

static void	init_mlx(t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, W, H, "DOOM");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl,
		&mlx->endian);
	mlx->editor.img = mlx_new_image(mlx->mlx, ((3 * W) / 4), H);
	mlx->editor.data = (int *)mlx_get_data_addr(mlx->editor.img,
		&mlx->editor.bpp, &mlx->editor.sl, &mlx->editor.endian);
}

int			main(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (0);
	if (!(mlx->mlx = mlx_init()))
		return (0);
	init(mlx);
	load_data(mlx);
	init_mlx(mlx);
	load_texture(mlx);
	mlx_hook(mlx->win, BUTTONPRESS, (1L<<2), shoot_key, mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, (1L<<6), mouse_hook, mlx);
	mlx_hook(mlx->win, KP, (1L<<0), ft_key_hook, mlx);
	mlx_hook(mlx->win, KEYRELEASE, (1L<<1), stop_movement, mlx);
	mlx_hook(mlx->win, DESTROYNOTIFY, (1L<<17), kill_mlx, mlx);
	music(mlx);
	mlx_loop_hook(mlx->mlx, expose, mlx);
	mlx_loop(mlx->mlx);
	unload_data(mlx);
	return (0);
}
