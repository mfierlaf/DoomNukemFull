/* ************************************************************************** */
/*	                                                                       */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:38:45 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 14:38:47 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static int		read_object(int i, char **split_line, t_mlx *mlx)
{
	printf("i: %d\n", i);
	mlx->objects[i].pos.x = atof(split_line[1]);
	mlx->objects[i].pos.y = atof(split_line[2]);
	mlx->objects[i].sector = ft_atoi(split_line[3]);
	mlx->objects[i].tex = ft_atoi(split_line[4]);
	mlx->objects[i].life = ft_atoi(split_line[5]);
	// mlx->objects[i].lootable = ft_atoi(split_line[6]);
	sprite_var(i, mlx);
	printf("life: %d\n", mlx->objects[i].life);
	printf("obj.x: %f\n", mlx->objects[i].pos.x);
	printf("obj.y: %f\n", mlx->objects[i].pos.y);
	printf("isbot: %d\n", mlx->objects[i].isbot);
	printf("tex: %d\n", mlx->objects[i].tex);
	printf("init tex: %d\n", mlx->objects[i].initial_tex);
	return (i++);
}

struct	xy*	read_map(char **split_line, t_mlx *mlx)
{
	int			num_vertices;
	struct xy	*vert;

	num_vertices = ft_atoi(split_line[1]);
	vert = malloc(num_vertices * sizeof(vert));
	mlx->num_sectors = ft_atoi(split_line[2]);
	mlx->sectors = malloc(mlx->num_sectors * sizeof(*mlx->sectors));
	return (vert);
}

struct	xy*	read_vertices(int *j, struct xy *vert, char **split_line)
{
	int			i;

	i = 1;
	while (split_line[++i])
	{
		vert[*j].y = atof(split_line[1]);
		vert[*j].x = atof(split_line[i]);
		++*j;
	}
	return (vert);
}

int			read_sector(int *k, struct xy *vert, char **split_line, t_mlx *mlx)
{
	int			vertex_len;
	int			n;

	vertex_len = 0;
	++*k;
	mlx->sectors[*k].floor = atof(split_line[1]);
	mlx->sectors[*k].ceil = atof(split_line[2]);
	while (split_line[vertex_len] != NULL)
		vertex_len++;
	vertex_len -= 3;
	mlx->sectors[*k].npoints = vertex_len / 2;
	vertex_len /= 2;
	mlx->sectors[*k].neighbors = malloc((vertex_len) * \
		sizeof(*mlx->sectors[*k].neighbors));
	mlx->sectors[*k].vertex = malloc((vertex_len + 1) * \
		sizeof(*mlx->sectors[*k].vertex));
	n = -1;
	while (++n < vertex_len)
		mlx->sectors[*k].neighbors[n] = ft_atoi(split_line[vertex_len + n + 3]);
	n = -1;
	while (++n < vertex_len)
		mlx->sectors[*k].vertex[n + 1] = vert[ft_atoi(split_line[n + 3])];
	mlx->sectors[*k].vertex[0] = mlx->sectors[*k].vertex[vertex_len];
	return (n);
}

void		read_player(int n, char **split_line, t_mlx *mlx)
{
	float		angle;
	struct xy	v;

	v.x = ft_atoi(split_line[1]);
	v.y = ft_atoi(split_line[2]);
	angle = ft_atoi(split_line[3]);
	n = ft_atoi(split_line[4]);
	mlx->player = (struct s_player) { 
		{v.x, v.y, 0}, {0, 0, 0}, angle, 0, 0, 0, n, 100, 0};
	mlx->player.where.z = mlx->sectors[mlx->player.sector].floor + EyeHeight;
}

void		load_data(t_mlx *mlx)
{
	int			fd;
	char		*line;
	char		**split_line;
	struct xy	*vert;
	int			n;
	int			j;
	int			k;
	int			i;

	j = 0;
	k = -1;
	i = 1;
	if ((fd = open("./map-clear.txt", O_RDONLY)) < 0)
		kill_mlx("ERROR IN MAP\n", mlx);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(split_line = ft_strsplit(line, ' ')))
			kill_mlx("ERROR IN MAP\n", mlx);
		if (split_line[0][0] == 'm')
			vert = read_map(split_line, mlx);
		else if (split_line[0][0] == 'v')
			vert = read_vertices(&j, vert, split_line);
		else if (split_line[0][0] == 's')
			n = read_sector(&k, vert, split_line, mlx);
		else if (split_line[0][0] == 'o')
			i = read_object(i, split_line, mlx);
		else if (split_line[0][0] == 'p')
			read_player(n, split_line, mlx);
	}
	close(fd);
	free(vert);
	free(line);
}

void		load_texture(t_mlx *mlx)
{
	int			width;
	int			height;

	width = TEXTURE_SIZE;
	height = TEXTURE_SIZE;
	mlx->tex[0].img = mlx_xpm_file_to_image(mlx->mlx, "textures/bookshelf.xpm", &width, &height);
	mlx->tex[0].data = (int *)mlx_get_data_addr(mlx->tex[0].img, &mlx->tex[0].bpp, &mlx->tex[0].sl, &mlx->tex[0].endian);
	mlx->tex[1].img = mlx_xpm_file_to_image(mlx->mlx, "textures/tcastron.xpm", &width, &height);
	mlx->tex[1].data = (int *)mlx_get_data_addr(mlx->tex[1].img, &mlx->tex[1].bpp, &mlx->tex[1].sl, &mlx->tex[1].endian);
	mlx->tex[2].img = mlx_xpm_file_to_image(mlx->mlx, "textures/mossy.xpm", &width, &height);
	mlx->tex[2].data = (int *)mlx_get_data_addr(mlx->tex[2].img, &mlx->tex[2].bpp, &mlx->tex[2].sl, &mlx->tex[2].endian);
	mlx->tex[3].img = mlx_xpm_file_to_image(mlx->mlx, "textures/colors.xpm", &width, &height);
	mlx->tex[3].data = (int *)mlx_get_data_addr(mlx->tex[3].img, &mlx->tex[3].bpp, &mlx->tex[3].sl, &mlx->tex[3].endian);
	mlx->tex[4].img = mlx_xpm_file_to_image(mlx->mlx, "textures/colors_big.xpm", &width, &height);
	mlx->tex[4].data = (int *)mlx_get_data_addr(mlx->tex[4].img, &mlx->tex[4].bpp, &mlx->tex[4].sl, &mlx->tex[4].endian);
	mlx->tex[5].img = mlx_xpm_file_to_image(mlx->mlx, "textures/colors_big_reversed.xpm", &width, &height);
	mlx->tex[5].data = (int *)mlx_get_data_addr(mlx->tex[5].img, &mlx->tex[5].bpp, &mlx->tex[5].sl, &mlx->tex[5].endian);
	

	mlx->tab_bmp[PRIEST_1] = new_bmp("textures/hitler_0_1.bmp");
	mlx->tab_bmp[PRIEST_2] = new_bmp("textures/hitler_0_2.bmp");
	mlx->tab_bmp[PRIEST_3] = new_bmp("textures/hitler_0_3.bmp");
	mlx->tab_bmp[PRIEST_4] = new_bmp("textures/hitler_0_4.bmp");
	mlx->tab_bmp[PRIEST_DEAD_1] = new_bmp("textures/hitler_1_0.bmp");
	mlx->tab_bmp[PRIEST_DEAD_2] = new_bmp("textures/hitler_1_1.bmp");
	mlx->tab_bmp[PRIEST_DEAD_3] = new_bmp("textures/hitler_1_2.bmp");
	mlx->tab_bmp[PRIEST_DEAD_4] = new_bmp("textures/hitler_1_3.bmp");
	mlx->tab_bmp[PRIEST_DEAD_5] = new_bmp("textures/hitler_1_4.bmp");
	mlx->tab_bmp[PRIEST_DEAD_6] = new_bmp("textures/hitler_1_5.bmp");
	mlx->tab_bmp[PRIEST_DEAD_7] = new_bmp("textures/hitler_1_6.bmp");

	mlx->tab_bmp[MECH_1] = new_bmp("textures/hitler_2_0.bmp");
	mlx->tab_bmp[MECH_2] = new_bmp("textures/hitler_2_1.bmp");
	mlx->tab_bmp[MECH_3] = new_bmp("textures/hitler_2_2.bmp");
	mlx->tab_bmp[MECH_4] = new_bmp("textures/hitler_2_3.bmp");
	mlx->tab_bmp[MECH_5] = new_bmp("textures/hitler_2_4.bmp");
	mlx->tab_bmp[MECH_6] = new_bmp("textures/hitler_2_5.bmp");
	mlx->tab_bmp[MECH_7] = new_bmp("textures/hitler_2_6.bmp");
	mlx->tab_bmp[MECH_DEAD_1] = new_bmp("textures/hitler_3_0.bmp");
	mlx->tab_bmp[MECH_DEAD_2] = new_bmp("textures/hitler_3_1.bmp");
	mlx->tab_bmp[MECH_DEAD_3] = new_bmp("textures/hitler_3_2.bmp");
	mlx->tab_bmp[MECH_DEAD_4] = new_bmp("textures/hitler_3_3.bmp");

	mlx->tab_bmp[NORMAL_1] = new_bmp("textures/hitler_4_0.bmp");
	mlx->tab_bmp[NORMAL_2] = new_bmp("textures/hitler_4_1.bmp");
	mlx->tab_bmp[NORMAL_3] = new_bmp("textures/hitler_4_2.bmp");
	mlx->tab_bmp[NORMAL_4] = new_bmp("textures/hitler_4_3.bmp");
	mlx->tab_bmp[NORMAL_5] = new_bmp("textures/hitler_4_4.bmp");
	mlx->tab_bmp[NORMAL_6] = new_bmp("textures/hitler_4_5.bmp");
	mlx->tab_bmp[NORMAL_7] = new_bmp("textures/hitler_4_6.bmp");
	mlx->tab_bmp[NORMAL_DEAD_1] = new_bmp("textures/hitler_5_0.bmp");
	mlx->tab_bmp[NORMAL_DEAD_2] = new_bmp("textures/hitler_5_1.bmp");
	mlx->tab_bmp[NORMAL_DEAD_3] = new_bmp("textures/hitler_5_2.bmp");
	mlx->tab_bmp[NORMAL_DEAD_4] = new_bmp("textures/hitler_5_3.bmp");
	mlx->tab_bmp[NORMAL_DEAD_5] = new_bmp("textures/hitler_5_4.bmp");
	mlx->tab_bmp[NORMAL_DEAD_6] = new_bmp("textures/hitler_5_5.bmp");
	mlx->tab_bmp[NORMAL_DEAD_7] = new_bmp("textures/hitler_5_6.bmp");
	mlx->tab_bmp[NORMAL_DEAD_8] = new_bmp("textures/hitler_5_7.bmp");

	mlx->tab_bmp[BACKGROUND] = new_bmp("textures/doom.bmp");
	mlx->tab_bmp[HAND_GUN] = new_bmp("textures/hand_gun.bmp");
	mlx->tab_bmp[MUTE] = new_bmp("textures/mute.bmp");
	mlx->tab_bmp[KNIFE] = new_bmp("textures/knife.bmp");
	mlx->tab_bmp[GUN] = new_bmp("textures/gun.bmp");
	mlx->tab_bmp[BIG_GUN] = new_bmp("textures/big_gun.bmp");
	mlx->tab_bmp[BLUE_KEY] = new_bmp("textures/blue_key.bmp");
	mlx->tab_bmp[SHIELD] = new_bmp("textures/shield.bmp");
	mlx->tab_bmp[ARMOR] = new_bmp("textures/armor.bmp");
	mlx->tab_bmp[BRICK] = new_bmp("textures/brick.bmp");
	mlx->tab_bmp[CHICKEN_LEG] = new_bmp("textures/chicken_leg.bmp");
	mlx->tab_bmp[MED_KIT] = new_bmp("textures/med_kit.bmp");
	mlx->tab_bmp[AMMO] = new_bmp("textures/ammo.bmp");
	mlx->tab_bmp[GOLDEN_KEY] = new_bmp("textures/golden_key.bmp");
	mlx->tab_bmp[CHALICE] = new_bmp("textures/chalice.bmp");
	mlx->tab_bmp[BULLET] = new_bmp("textures/bullet.bmp");


	mlx->tab_anim[CARABIN_ANIM_0] = new_bmp("textures/carabin_0.bmp");
	mlx->tab_anim[CARABIN_ANIM_1] = new_bmp("textures/carabin_1.bmp");
	mlx->tab_anim[CARABIN_ANIM_2] = new_bmp("textures/carabin_2.bmp");
	mlx->tab_anim[CARABIN_ANIM_3] = new_bmp("textures/carabin_3.bmp");
	mlx->tab_anim[CARABIN_ANIM_4] = new_bmp("textures/carabin_4.bmp");
	mlx->tab_anim[GATLIN_ANIM_0] = new_bmp("textures/gatling_0.bmp");
	mlx->tab_anim[GATLIN_ANIM_1] = new_bmp("textures/gatling_1.bmp");
	mlx->tab_anim[GATLIN_ANIM_2] = new_bmp("textures/gatling_2.bmp");
	mlx->tab_anim[GATLIN_ANIM_3] = new_bmp("textures/gatling_3.bmp");
	mlx->tab_anim[GATLIN_ANIM_4] = new_bmp("textures/gatling_4.bmp");
	mlx->tab_anim[GUN_ANIM_0] = new_bmp("textures/gun_0.bmp");
	mlx->tab_anim[GUN_ANIM_1] = new_bmp("textures/gun_1.bmp");
	mlx->tab_anim[GUN_ANIM_2] = new_bmp("textures/gun_2.bmp");
	mlx->tab_anim[GUN_ANIM_3] = new_bmp("textures/gun_3.bmp");
	mlx->tab_anim[GUN_ANIM_4] = new_bmp("textures/gun_4.bmp");
	mlx->tab_anim[KNIFE_ANIM_0] = new_bmp("textures/knife_0.bmp");
	mlx->tab_anim[KNIFE_ANIM_1] = new_bmp("textures/knife_1.bmp");
	mlx->tab_anim[KNIFE_ANIM_2] = new_bmp("textures/knife_2.bmp");
	mlx->tab_anim[KNIFE_ANIM_3] = new_bmp("textures/knife_3.bmp");
	mlx->tab_anim[KNIFE_ANIM_4] = new_bmp("textures/knife_4.bmp");
}

void		unload_data(t_mlx *mlx)
{
	unsigned	a;

	a = -1;
	while (++a < mlx->num_sectors)
		free(mlx->sectors[a].vertex);
	a = -1;
	while (++a < mlx->num_sectors)
		free(mlx->sectors[a].neighbors);
	free(mlx->sectors);
	mlx->sectors = NULL;
	mlx->num_sectors = 0;
}
