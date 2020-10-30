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

int	main(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (0);
	if (!(mlx->mlx = mlx_init()))
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, W, H, "DOOM");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl,
		&mlx->endian);
	init(mlx);
	load_data(mlx);
	load_texture(mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, POINTERMOTIONMASK, mouse_hook, mlx);
	mlx_hook(mlx->win, KP, KPMASK, ft_key_hook, mlx);
	mlx_hook(mlx->win, KEYRELEASE, KEYRELEASEMASK, stop_movement, mlx);
	mlx_hook(mlx->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, kill_mlx, mlx);
	// menu(mlx);
	mlx_loop_hook(mlx->mlx, expose, mlx);
	mlx_loop(mlx->mlx);
	unload_data(mlx);
	return (0);
}
