/* ************************************************************************** */
/*                                                                            */
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

void load_data(t_mlx *mlx)
{
	FILE* fp = fopen("./map-clear.txt", "rt");
	if(!fp) { perror("./map-clear.txt"); exit(1); }
	char Buf[256], word[256], *ptr;
	struct xy* vert = NULL, v;
	int n , m, NumVertices = 0;
	while(fgets(Buf, sizeof Buf, fp))
		switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
			case 'v': // vertex
				for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
				{ vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
				break;
			case 's': // sector
			  mlx->sectors = realloc(mlx->sectors, ++mlx->num_sectors * sizeof(*mlx->sectors));
				t_sector* sect = &mlx->sectors[mlx->num_sectors-1];
				int* num = NULL;
				sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
				for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
				{ num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
				sect->npoints   = m /= 2;
				sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
				sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
				for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
				for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
				sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
				free(num);
				break;
			case 'p':; // player
					 float angle;
					 sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
					 mlx->player = (struct s_player) { {v.x, v.y, 0}, {0,0,0}, angle,0,0,0, n }; // TODO: Range checking
					 mlx->player.where.z = mlx->sectors[mlx->player.sector].floor + EyeHeight;
		}
	fclose(fp);
	free(vert);
}

void load_texture(t_mlx *mlx)
{
	int    width;
    int    height;

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
    mlx->tab_bmp[0] = new_bmp("textures/minecraft_texture.bmp");
    mlx->tab_bmp[BACKGROUND] = new_bmp("textures/doom.bmp");
    mlx->tab_bmp[HAND_GUN] = new_bmp("textures/hand_gun.bmp");
    mlx->tab_bmp[MUTE] = new_bmp("textures/mute.bmp");
    mlx->tab_bmp[KNIFE] = new_bmp("textures/knife.bmp");
    mlx->tab_bmp[GUN] = new_bmp("textures/gun.bmp");
    mlx->tab_bmp[BIG_GUN] = new_bmp("textures/big_gun.bmp");
    mlx->tab_bmp[BLUE_KEY] = new_bmp("textures/blue_key.bmp");
	mlx->tab_bmp[SHIELD] = new_bmp("textures/shield.bmp");

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

void unload_data(t_mlx *mlx)
{
	unsigned a;

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
