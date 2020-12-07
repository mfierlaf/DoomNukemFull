/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"

static void		load_texture4(t_mlx *mlx)
{
	mlx->tab_bmp[MULTI_1] = new_bmp("textures/multi1.bmp");
	mlx->tab_bmp[MULTI_2] = new_bmp("textures/multi2.bmp");
	mlx->tab_bmp[MULTI_3] = new_bmp("textures/multi3.bmp");
	mlx->tab_bmp[MULTI_4] = new_bmp("textures/multi4.bmp");
	mlx->tab_bmp[MULTI_5] = new_bmp("textures/multi5.bmp");
	mlx->tab_bmp[MULTI_6] = new_bmp("textures/multi6.bmp");
	mlx->tab_bmp[MULTI_7] = new_bmp("textures/multi7.bmp");
	mlx->tab_bmp[MULTI_8] = new_bmp("textures/multi8.bmp");
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
}

static void		load_texture3(t_mlx *mlx)
{
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
}

static void		load_texture2(t_mlx *mlx)
{
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
}

void			load_texture(t_mlx *mlx)
{
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
	load_texture2(mlx);
	load_texture3(mlx);
	load_texture4(mlx);
	mlx->tab_bmp[SKY] = new_bmp("textures/sky.bmp");
	mlx->tab_bmp[GATE] = new_bmp("textures/gate.bmp");
	mlx->tab_bmp[MOSSY] = new_bmp("textures/mossy.bmp");
	mlx->tab_bmp[TCASTRON] = new_bmp("textures/tcastron.bmp");
	mlx->tab_bmp[MINECRAFT] = new_bmp("textures/minecraft_texture.bmp");
	mlx->tab_anim[KNIFE_ANIM_0] = new_bmp("textures/knife_0.bmp");
	mlx->tab_anim[KNIFE_ANIM_1] = new_bmp("textures/knife_1.bmp");
	mlx->tab_anim[KNIFE_ANIM_2] = new_bmp("textures/knife_2.bmp");
	mlx->tab_anim[KNIFE_ANIM_3] = new_bmp("textures/knife_3.bmp");
	mlx->tab_anim[KNIFE_ANIM_4] = new_bmp("textures/knife_4.bmp");
	valid_bmp(mlx);
}
