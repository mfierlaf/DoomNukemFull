/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H

# define DEFINE_H

# define NB_OBJ						4
# define NB_DECO					1
# define DIFF_BMP					66
# define FILTER_COLOR				0x980088
# define W							1200
# define H							800
# define TEXTURE_SIZE				64
# define JUMP_SPEED					0.03f
# define SPEED						0.1f
# define EYEHEIGHT					6
# define DUCKHEIGHT					2.5
# define HEADMARGIN					1
# define KNEEHEIGHT					2
# define HFOV						0.486666667f
# define VFOV						0.2f

/*
** LINUX KEYS
*/
# define RIGHT_ARROW				65363
# define DOWN_ARROW					65364
# define LEFT_ARROW					65361
# define UP_ARROW					65362
# define ESC						65307
# define SP							32
# define LCTRL						65507
# define W_LN						119
# define A_LN						97
# define S_LN						115
# define D_LN						100
# define E_LN						101
# define F_LN						102
# define M_LN						109
# define Q_LN						113
# define L_LN						108
# define ENTR_LN					65293
# define K1_LN						38
# define K2_LN						233
# define K3_LN						34
# define K4_LN						39
# define K5_LN						40

# define PRIEST_1					0
# define PRIEST_2					1
# define PRIEST_3					2
# define PRIEST_4					3
# define PRIEST_DEAD_1				4
# define PRIEST_DEAD_2				5
# define PRIEST_DEAD_3				6
# define PRIEST_DEAD_4				7
# define PRIEST_DEAD_5				8
# define PRIEST_DEAD_6				9
# define PRIEST_DEAD_7				10
# define MECH_1						11
# define MECH_2						12
# define MECH_3						13
# define MECH_4						14
# define MECH_5						15
# define MECH_6						16
# define MECH_7						17
# define MECH_DEAD_1				18
# define MECH_DEAD_2				19
# define MECH_DEAD_3				20
# define MECH_DEAD_4				21
# define NORMAL_1					22
# define NORMAL_2					23
# define NORMAL_3					24
# define NORMAL_4					25
# define NORMAL_5					26
# define NORMAL_6					27
# define NORMAL_7					28
# define NORMAL_DEAD_1				29
# define NORMAL_DEAD_2				30
# define NORMAL_DEAD_3				31
# define NORMAL_DEAD_4				32
# define NORMAL_DEAD_5				33
# define NORMAL_DEAD_6				34
# define NORMAL_DEAD_7				35
# define NORMAL_DEAD_8				36

# define ANIM_NB					20
# define CARABIN_ANIM_0				0
# define CARABIN_ANIM_1				1
# define CARABIN_ANIM_2				2
# define CARABIN_ANIM_3				3
# define CARABIN_ANIM_4				4
# define GATLIN_ANIM_0				5
# define GATLIN_ANIM_1				6
# define GATLIN_ANIM_2				7
# define GATLIN_ANIM_3				8
# define GATLIN_ANIM_4				9
# define GUN_ANIM_0					10
# define GUN_ANIM_1					11
# define GUN_ANIM_2					12
# define GUN_ANIM_3					13
# define GUN_ANIM_4					14
# define KNIFE_ANIM_0				15
# define KNIFE_ANIM_1				16
# define KNIFE_ANIM_2				17
# define KNIFE_ANIM_3				18
# define KNIFE_ANIM_4				19

# define BRICK						37
# define BACKGROUND					38
# define HAND_GUN					39
# define MUTE						40
# define KNIFE						41
# define GUN						42
# define BIG_GUN					43
# define BLUE_KEY					44
# define SHIELD						45
# define ARMOR						46
# define CHICKEN_LEG				47
# define MED_KIT					48
# define AMMO						49
# define GOLDEN_KEY					50
# define CHALICE					51
# define BULLET						52
# define SKY						53
# define GATE						54
# define MOSSY						55
# define TCASTRON					56
# define MULTI_1					57
# define MULTI_2					58
# define MULTI_3					59
# define MULTI_4					60
# define MULTI_5					61
# define MULTI_6					62
# define MULTI_7					63
# define MULTI_8					64
# define MINECRAFT					65
/*
**# define NOEVENTMASK				0L
**# define KPMASK 					(1L<<0)
**# define KEYRELEASEMASK				(1L<<1)
**# define BUTTONPRESSMASK			(1L<<2)
**# define BUTTONRELEASEMASK			(1L<<3)
**# define ENTERWINDOWMASK			(1L<<4)
**# define LEAVEWINDOWMASK			(1L<<5)
**# define POINTERMOTIONMASK			(1L<<6)
**# define POINTERMOTIONHINTMAS		(1L<<7)
**# define BUTTON1MOTIONMASK			(1L<<8)
**# define BUTTON2MOTIONMASK			(1L<<9)
**# define BUTTON3MOTIONMASK			(1L<<10)
**# define BUTTON4MOTIONMASK			(1L<<11)
**# define BUTTON5MOTIONMASK			(1L<<12)
**# define BUTTONMOTIONMASK			(1L<<13)
**# define KEYMAPSTATEMASK			(1L<<14)
**# define EXPOSUREMASK				(1L<<15)
**# define VISIBILITYCHANGEMASK		(1L<<16)
**# define STRUCTURENOTIFYMASK		(1L<<17)
**# define RESIZEREDIRECTMASK			(1L<<18)
**# define SUBSTRUCTURENOTIFYMASK		(1L<<19)
**# define SUBSTRUCTUREREDIRECTMASK	(1L<<20)
**# define FOCUSCHANGEMASK			(1L<<21)
**# define PROPERTYCHANGEMASK			(1L<<22)
**# define COLORMAPCHANGEMASK			(1L<<23)
**# define OWNERGRABBUTTONMASK		(1L<<24)
*/
# define KP							2
# define KEYRELEASE					3
# define BUTTONPRESS				4
# define BUTTONRELEASE				5
# define MOTIONNOTIFY				6
# define ENTERNOTIFY				7
# define LEAVENOTIFY				8
# define FOCUSIN					9
# define FOCUSOUT					10
# define KEYMAPNOTIFY				11
# define EXPOSE						12
# define GRAPHICSEXPOSE				13
# define NOEXPOSE					14
# define VISIBILITYNOTIFY			15
# define CREATENOTIFY				16
# define DESTROYNOTIFY				17
# define UNMAPNOTIFY				18
# define MAPNOTIFY					19
# define MAPREQUEST					20
# define REPARENTNOTIFY				21
# define CONFIGURENOTIFY			22
# define CONFIGUREREQUEST			23
# define GRAVITYNOTIFY				24

# define BUT1_KEY					1
# define BUT2_KEY					2
# define BUT3_KEY					3
# define SCROLLUP_KEY				4
# define SCROLLDOWN_KEY				5
# define SCROLLLEFT_KEY				6
# define SCROLLRIGHT_KEY			7

# define A_KEY						0
# define B_KEY						11
# define C_KEY						8
# define D_KEY						2
# define E_KEY						14
# define F_KEY						3
# define G_KEY						5
# define H_KEY						4
# define I_KEY						34
# define J_KEY						38
# define K_KEY						40
# define L_KEY						37
# define M_KEY						46
# define N_KEY						45
# define O_KEY						31
# define P_KEY						35
# define Q_KEY						12
# define R_KEY						15
# define S_KEY						1
# define T_KEY						17
# define U_KEY						32
# define V_KEY						9
# define W_KEY						13
# define X_KEY						7
# define Y_KEY						16
# define Z_KEY						6

# define K1_KEY						18
# define K2_KEY						19
# define K3_KEY						20
# define K4_KEY						21
# define K5_KEY						23
# define K6_KEY						22
# define K7_KEY						26
# define K8_KEY						28
# define K9_KEY						25
# define K0_KEY						29

# define SP_KEY						49
# define BQ_KEY						50
# define MN_KEY						27
# define PL_KEY						24
# define SBO_KEY					33
# define SBC_KEY					30
# define BSL_KEY					42
# define SC_KEY						41
# define SQ_KEY						39
# define CM_KEY						43
# define PT_KEY						47
# define SL_KEY						44

# define F1_KEY						122
# define F2_KEY						120
# define F3_KEY						99
# define F4_KEY						118
# define F5_KEY						96
# define F6_KEY						97
# define F7_KEY						98
# define F8_KEY						100
# define F9_KEY						101
# define F10_KEY					109
# define F12_KEY					111
# define F13_KEY					105
# define F14_KEY					107
# define F15_KEY					113
# define F16_KEY					106
# define F17_KEY					64
# define F18_KEY					79
# define F19_KEY					80

# define UP_KEY						126
# define DOWN_KEY					125
# define RIGHT_KEY					124
# define LEFT_KEY					123

# define ESC_KEY					53
# define TAB_KEY					48
# define CL_KEY						272
# define LSFT_KEY					257
# define LCTRL_KEY					256
# define LOPT_KEY					261
# define LCMD_KEY					259
# define LDEL_KEY					51
# define RTN_KEY					36
# define RSFT_KEY					258
# define RCTRL_KEY					269
# define ROPT_KEY					262
# define RCMD_KEY					260
# define FN_KEY						279
# define RDEL_KEY					117
# define HOME_KEY					115
# define END_KEY					119
# define PUP_KEY					116
# define PDOWN_KEY					121
# define CLR_KEY					71

# define NK0_KEY					82
# define NK1_KEY					83
# define NK2_KEY					84
# define NK3_KEY					85
# define NK4_KEY					86
# define NK5_KEY					87
# define NK6_KEY					88
# define NK7_KEY					89
# define NK8_KEY					91
# define NK9_KEY					92
# define NKEQ_KEY					81
# define NKSL_KEY					75
# define NKWC_KEY					67
# define NKMN_KEY					78
# define NKPL_KEY					69
# define NKPT_KEY					65
# define NKNTR_KEY					76

# define APPLE						0x3FF73F
# define ORANGE						0xFF9950
# define RED						0xFF0000
# define TEAL						0x1392A5

# define NB_BUTTON					5
# define BUTTON_ADD_SECTOR				2
# define BUTTON_MOD_VERTEX				3

# define DEFAULT_BUTTON_COLOUR				RED
# define PRESSED_BUTTON_COLOUR				ORANGE

# define NB_SECT_MAX					50

#endif
