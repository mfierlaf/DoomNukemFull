/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:01:03 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/05 15:01:05 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H

# define DOOM_NUKEM_H

# include "../minilibx_linux/mlx.h"

/*
** # include "../minilibx_macos/mlx.h"
*/
# include "define.h"
# include <stdlib.h>
# include <math.h>
# include "../libft/incl/libft.h"
# include <stdint.h>
# include <fcntl.h>

typedef struct			s_bmp_header
{
	uint16_t			type;
	uint16_t			size_1;
	uint16_t			size_2;
	uint16_t			reserved1;
	uint16_t			reserved2;
	uint16_t			offset1;
	uint16_t			offset2;
	uint16_t			dib_header_size1;
	uint16_t			dib_header_size2;
	int16_t				width_px1;
	int16_t				width_px2;
	int16_t				height_px1;
	int16_t				height_px2;
	uint16_t			num_planes;
	uint16_t			bits_per_pixel;
	uint16_t			compression1;
	uint16_t			compression2;
	uint16_t			image_size_bytes1;
	uint16_t			image_size_bytes2;
	int16_t				x_resolution_ppm1;
	int16_t				x_resolution_ppm2;
	int16_t				y_resolution_ppm1;
	int16_t				y_resolution_ppm2;
	uint16_t			num_colors1;
	uint16_t			num_colors2;
	uint16_t			important_colors1;
	uint16_t			important_colors2;
}						t_bmp_header;

typedef struct        s_bmp_header_f
{
  int           type;
  int           size;
  uint16_t        reserved1;
  uint16_t        reserved2;
  int           offset;
  int           dib_header_size;
  int           width_px;
  int           height_px;
  int           num_planes;
  int           bits_per_pixel;
  int           compression;
  int           image_size_bytes;
  int           x_res;
  int           y_res;
  int           num_colors;
  int           important_colors;
  int           padding;
}             t_bmp_header_f;

typedef struct        s_bmp
{
  t_bmp_header_f      header;
  int           *data;
  int           nb;
}             t_bmp;

typedef struct        s_color
{
  int           off_r;
  int           off_b;
  int           off_g;
}             t_color;

typedef struct			s_pos
{
	float				x;
	float				y;
	float				z;
}						t_pos;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_fpoint
{
	float					x;
	float					y;
}						t_fpoint;

typedef struct			s_line
{
	t_pos				orig;
	t_pos				end;
}						t_line;

typedef struct			s_menu
{
	int					on;
	int					gun_pointer;
	int					bot_level;
}						t_menu;

typedef struct			s_sprites
{
	int					line_height;
	int					draw_start;
	int					draw_end;
	float				dist;
	float				dist_ps;
	float				dist_pa;
	float				angle;
	float				off_angle;
	float				slice;
	t_pos				inter;
	t_pos				pl_pos;
	t_pos				a;
	t_pos				b;
	t_pos				sp_pos;
	t_pos				rel_dir;
	t_line				deco_line;
	t_bmp				*curr_bmp;
}						t_sprites;

typedef struct			s_vsl
{
	int					y;
	int					y_max;
	int					color;
	int					i;
	float				dx;
	float				dy;
	float				rel_x;
	float				rel_y;
}						t_vsl;

typedef struct			s_vl
{
	int					x;
	int					y1;
	int					y2;
	unsigned			txtx;
}						t_vl;

typedef struct			s_inter
{
	float				c1;
	float				c2;
	float				slope1;
	float				slope2;
	t_line				line1;
	t_line				line2;
}						t_inter;
typedef struct			s_obj
{
	unsigned int		sector;
	int					tex;
	int					lootable;
	t_pos				pos;
	t_line				sprite_line;
	int					order;
	float				distance;
	int					life;
	int					isbot;
	int					initial_tex;
	int					nb_anim_walk;
	int					nb_anim;
}						t_obj;

typedef struct			s_shoot
{
	float			off_angle;
	float			angle;
	float			slice;
	int				sprite;
	t_pos			inter;
	t_pos			pl_pos;
	t_line			straight_ray;
	t_line			small_ray;
	t_pos			dir;
}						t_shoot;
typedef struct			s_deco
{
	int					tex;
	int					sector;
	int					wall;
	t_pos				origin;
	t_pos				end;
}						t_deco;

typedef struct			s_music
{
	int					mute;
	int					music;
	char				*name;
}						t_music;

typedef struct			s_inventory
{
	int					ammo;
	int					weapon_type[4];
	int					keys;
	int					shield;
	int					count;
	int					grail;
}						t_inventory;

typedef struct			s_weapon
{
	int					anim;
	int					damage;
	t_point				dir_shoot;
}						t_weapon;

typedef struct			s_sleep
{
	int					walk;
	int					shoot;
	int					death;
}						t_sleep;

typedef struct			s_anim
{
	int					started;
	int					curr_anim_walk;
	int					curr_anim;
	int					shoot;
}						t_anim;

typedef struct			s_xyz
{
	float				x;
	float				y;
	float				z;
}						t_xyz;

typedef struct			s_xy
{
	float				x;
	float				y;
}						t_xy;

typedef struct			s_player
{
	t_xyz				where;
	t_xyz				velocity;
	float				angle;
	float				anglesin;
	float				anglecos;
	float				yaw;
	unsigned			sector;
	int					life;
	int					is_dead;
}						t_player;

typedef struct			s_scale
{
	int					a;
	int					b;
	int					c;
	int					d;
	int					f;
}						t_scale;

typedef struct			s_sector
{
	int					brightness;
	int					sky;
	float				floor;
	float				ceil;
	t_xy				*vertex;
	int					*v_id;
	signed char			*neighbors;
	unsigned			npoints;
}						t_sector;

typedef struct			s_expose
{
	float				eyeheight;
	float				nextz;
	float				px;
	float				py;
	float				dx;
	float				dy;
	t_xy				*vert;
	float				yaw;
	unsigned			s;
	float				hole_low;
	float				hole_high;
	float				xd;
	float				yd;
	float				move_vec[2];
	int					pushing;
	float				acceleration;
	t_sector			*sect;
}						t_expose;

typedef struct			s_tex
{
	void				*img;
	int					*data;
	int					bpp;
	int					sl;
	int					endian;
	int					*tex_ternary;
}						t_tex;

typedef	struct			s_bham
{
	int					dx;
	int					dy;
	int					err;
	int					sx;
	int					sy;
	int					e2;
}						t_bham;

typedef struct			s_button
{
	t_point				orig;
	t_point				end;
	int					color;
	int					pressed;
	int					toggled;
}						t_button;

typedef struct			s_editor
{
	int					map_img_width;
	int					on;
	void				*img;
	int					*data;
	int					endian;
	int					sl;
	int					bpp;
	int 				sqr_size;
	int					off_x;
	int					off_y;
	int					old_x;
	int					old_y;
	void				*img_map;
	int					*data_map;
	void				*img_buttons;
	int					*data_buttons;
	int					buttons_img_width;
	int					closest_sector;
	int					closest_vertex;
	int					closest_sector2;
	int					closest_vertex2;
	t_fpoint			start;
	t_fpoint			end;
	t_button			buttons[NB_BUTTON];
	int					button_toggled;
}						t_editor;

typedef struct			s_item
{
	int					sectorno;
	int					sx1;
	int					sx2;
}						t_item;

typedef struct			s_scaler
{
	int					result;
	int					bop;
	int					fd;
	int					ca;
	int					cache;
}						t_scaler;

typedef struct			s_load
{
	int					n;
	int					i;
	int					j;
	int					k;
	int					l;
	int					fd;
	char				*line;
	char				**split_line;
	t_xy				*vert;
}						t_load;

typedef struct			s_draw
{
	float				mapx;
	float				mapz;
	int					neighbor;
	int					y2a;
	int					y1a;
	int					y1b;
	int					y2b;
	int					ny1a;
	int					ny2a;
	int					ny1b;
	int					ny2b;
	float				pcos;
	float				psin;
	float				yceil;
	float				yfloor;
	int					ytop[W];
	int					ybottom[W];
	t_scaler			ya_int;
	t_scaler			yb_int;
	int					x1;
	int					x2;
	float				tz1;
	float				tz2;
	int					u1;
	int					u0;
	int					endx;
	int					beginx;
	int					txtx;
	int					z;
	int					ya;
	int					yb;
	int					cya;
	int					cyb;
	float				tx1;
	float				tx2;
	t_item				now;
	t_sector			*sect;
	int					check;
	int					maxqueue;
	t_item				queue[32];
	t_item				*head;
	t_item				*tail;
	int					*renderedsectors;
	t_xy				i1;
	t_xy				i2;
	float				nearz;
	float				yscale1;
	float				yscale2;
	float				mapy;
	int					nya;
	int					nyb;
	int					cnya;
	int					tex;
}						t_draw;

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	int					*data;
	int					endian;
	int					sl;
	int					bpp;
	int					color;
	unsigned int		num_sectors;
	int					wasd[4];
	int					ground;
	int					falling;
	int					flying;
	int					ducking;
	int					moving;
	int					*vert_tex;
	unsigned			txty;
	int					*tex_ternary;
	t_line				ray;
	t_menu				menu;
	t_music				music;
	t_weapon			weapon;
	t_inventory			inventory;
	t_anim				anim;
	t_sleep				sleep;
	t_bmp				*tab_anim[ANIM_NB];
	t_bmp				*tab_bmp[DIFF_BMP];
	t_obj				objects[NB_OBJ];
	t_deco				decos[NB_DECO];
	t_editor			editor;
	t_point				mouse;
	t_player			player;
	t_sector			*sectors;
	t_bham 				bham;
	t_fpoint			mouse_map;
}						t_mlx;
/*
** ANIM.C
*/
void					shoot_anim(t_mlx *mlx);
void					sprite_anim_death(int sprite, t_mlx *mlx);
void					sprite_anim_walk(int sprite, t_mlx *mlx);
/*
** BMP.C
*/
t_bmp					*new_bmp(char *str);
int						get_color(t_bmp *bmp, int x, int y);
int						check_tab_bmp(t_mlx *mlx);
int						read_color_vertical(t_bmp *bmp, int x, int y, \
							unsigned char *data);
/*
** BMP_2.C
*/
void					*free_bmp(t_bmp *bmp, int *data, unsigned char *tmp);
t_bmp					*read_img_bmp(char *file, t_bmp_header_f header);
int						convert_to_32(uint16_t left, uint16_t right);
t_bmp_header_f			convert_to_header(t_bmp_header src);
/*
** BMP_3.C
*/
t_bmp					*read_header_bmp(char *file);
void					valid_anim(t_mlx *mlx);
void					valid_bmp(t_mlx *mlx);
/*
** BOTS.C
*/
void					bot(int sprite, t_mlx *mlx);
/*
** BRESENHAM.C
*/
void					bresenham(t_mlx *mlx, int color);
void					dashed_bresenham(t_mlx *mlx, int color);
/*
** DECO.C
*/
void					draw_deco(int x, t_mlx *mlx);
/*
** DRAW.C
*/
void					draw_screen(t_mlx *mlx);
void					render(t_mlx *mlx, t_draw *draw);
void					render_declaration(t_mlx *mlx, t_draw *draw, int s);
void					draw_start(t_mlx *mlx, t_draw *draw);
/*
** DRAW2.C
*/
void					boucle_drawing(t_mlx *mlx, t_draw *draw, int x);
void					draw_vline(t_mlx *mlx, t_draw *draw, int x);
/*
** DRAW3.C
*/
void					check_edge(t_mlx *mlx, t_draw *draw);
int						perspective(t_mlx *mlx, t_draw *draw, int s);
void					players_view_tz2(t_draw *draw);
void					players_view(t_draw *draw);
/*
** DRAW4.C
*/
void					deco_while(t_mlx *mlx);
void					behind_player(t_draw *draw);
void					drawing(t_mlx *mlx, t_draw *draw);
/*
** EVENT.C
*/
int						mouse_hook(int x, int y, t_mlx *mlx);
int						mouse_release(int key, int x, int y, t_mlx *mlx);
int						ft_key_hook(int key, t_mlx *mlx);
int						stop_movement(int key, t_mlx *mlx);
int						button_mouse(int key, int x, int y, t_mlx *mlx);
/*
** EXPOSE.C
*/
int						expose(t_mlx *mlx);
void					gameplay(t_mlx *mlx);
/*
** FREE.C
*/
void					free_draw(t_draw *draw);
void					free_lines(t_load *load);
/*
** GAME.C
*/
void					game(t_mlx *mlx, t_expose ex);
/*
** GEOMETRY.C
*/
//t_line					new_line(t_fpoint pos1, t_fpoint pos2);
float					get_dist_mouse_to_map(t_fpoint p1, t_fpoint p2);
t_fpoint				new_fpoint(float x, float y);
int					is_inside(t_point p, t_button b);
/*
** HUD.C
*/
void					draw_hud(t_mlx *mlx);
/*
** INIT.C
*/
void					init(t_mlx *mlx);
void					sprite_var(int sprite, t_mlx *mlx);
/*
** LOAD.C
*/
void					load_data(t_mlx *ml);
void					unload_data(t_mlx *mlx);
/*
** LOAD_TEXTURES.C
*/
void					load_texture(t_mlx *mlx);
/*
** LOOT.C
*/
void					pick_up_loot(t_mlx *mlx);
/*
** MAP_EDITOR.C
*/
int					check_button_pressed(t_mlx *mlx);
void					init_buttons(t_mlx *mlx);
void					toggle_button(t_mlx *mlx, int button);
void					map_editor(t_mlx *mlx);
/*
** MENU.C
*/
void					story(t_mlx *mlx);
void					menu(t_mlx *mlx);
/*
** MENU2.C
*/
void					menu_strings(t_mlx *mlx);
void					music(t_mlx *mlx);
void					draw_image(t_point point, float zoom, t_bmp *bmp, \
							t_mlx *mlx);
/*
** MENU_KEYS.C
*/
void					menu_key_hook(int key, t_mlx *mlx);
/*
** MOVE.C
*/
void					move_player(t_mlx *mlx, float dx, float dy);
/*
** MULTI_SPRITES.C
*/
void					sort_sprites(t_mlx *mlx);
int						double_swap(t_mlx *mlx, int i, int j);
void					multi_sprites(int sprite, t_mlx *mlx);
/*
** READ_MAP.C
*/
int						read_sector(int *k, t_xy *vert,
							char **split_line, t_mlx *mlx);
void					read_player(int n, char **split_line, t_mlx *mlx);
t_xy					*read_vertices(int *j, t_xy *vert,
							char **split_line, t_mlx *mlx);
t_xy					*read_map(char **split_line, t_mlx *mlx);
/*
** SECTOR_MALLOC.C
*/
void					sector_malloc(t_mlx *mlx, int v_l, int *k);
/*
** SHAPE.C
*/
void					draw_pixel(int x, int y, t_mlx *mlx);
t_point					new_point(int x, int y);
void					line(t_point o, t_point e, t_mlx *mlx);
void					filled_rect(t_point size, int x, int y, t_mlx *mlx);
void					draw_rect(t_point size, int x, int y, t_mlx *mlx);
/*
** SKYBOX.C
*/
void					draw_skybox(t_mlx *mlx, int x);
/*
** SPRITES.C
*/
void					draw_sprites(int x, t_mlx *mlx);
void					vertical_sprite_lines(t_mlx *mlx, int x,
							t_sprites sprite, int i);
/*
** TOOLS.C
*/
float					point_side(t_pos p, t_pos start, t_pos end);
int						intersect_box(t_pos p0, t_pos p1, t_pos p2, t_pos p3);
t_xy					intersect(t_pos p0, t_pos p1, t_pos p2, t_pos p3);
char					check_valid_inter(t_pos inter, t_line line1, \
							t_line line2);
float					get_slope(t_line line);
/*
** TOOLS2.C
*/
t_pos					get_intersection(t_line line1, t_line line2, \
							float slope1, float slope2);
float					get_dist(t_pos p1, t_pos p2);
float					get_angle(t_pos p1, t_pos rel_dir);
int						valid_pixel(int x, int y);
/*
** TOOLS3.C
*/
double					clamp(double a, double b, double c);
int						overlap(double a, double b, double c, double d);
float					vxs(float a, float b, float c, float d);
double					max(double a, double b);
double					min(double a, double b);
/*
** TOOLS4.C
*/
void					clear_img(int *data, int w, int h);
int						kill_mlx(char *message, t_mlx *mlx);
float					yaw(float y, float z, t_mlx *mlx);
t_pos					new_pos(float x, float y);
t_line					new_line(t_pos orig, t_pos end);
/*
** VLINE.C
*/
void					vertical_line(t_draw *draw, t_vl vl,
							t_scaler ty, t_mlx *mlx);
t_vl					new_vl(int x, int y1, int y2, unsigned txtx);
t_scale					new_scale(int a, int b, int c, t_point de);
int						scaler_next(t_scaler *i);
t_scaler				scaler_init(t_scale scale);
/*
** WEAPON.C
*/
void					weapon_choice(t_mlx *mlx);
void					shoot(t_mlx *mlx);
void					send_bullet(t_mlx *mlx);
void					shoot_direction(t_mlx *mlx);
/*
** WEAPON2.C
*/
void					shoot_while(t_shoot *shoot, t_mlx *mlx);
#endif
