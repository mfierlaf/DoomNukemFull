#ifndef DOOM_NUKEM_H

# define DOOM_NUKEM_H

# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/incl/libft.h"
# include "keycode.h"
# include <stdint.h>
# include <fcntl.h>
/*LINUX*/
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define UP_ARROW 65362
# define ESC 65307
# define SP 32
# define LCTRL 65507
# define W_LN 119
# define A_LN 97
# define S_LN 115
# define D_LN 100
# define E_LN 101
# define Q_LN 113
# define R_LN 114
# define ENTR_LN 65293
# define K1_LN 38
# define K2_LN 233
# define K3_LN 34
# define K4_LN 39
# define K5_LN 40
/*COLORS*/
# define BLACK                0x000000
# define WHITE                0xFFFFFF
# define FILTER_COLOUR        0x980088
# define RED                0xFF0000
# define GREEN                0x00FF00
# define ORANGE                0xFF9950
# define BLUE                0x0000FF
# define GREY                0x696969
# define LIGHT_BLUE            0x00D5FF
# define PINK                0xF61DD9
# define PURPLE                0x9A0AC6
# define TEAL                0x1392A5
# define APPLE                0x3FF73F

# define DIFF_BMP 28
# define FILTER_COLOR 0x980088
# define W 1200
# define H 800
# define TEXTURE_SIZE 64
# define JUMP_SPEED 0.03f
# define SPEED 0.1f
# define EyeHeight  6    // Camera height from floor when standing
# define DuckHeight 2.5  // And when crouching
# define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
# define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
# define HFOV (0.73f * H / W)  // Affects the horizontal field of vision
# define VFOV (0.2f)    // Affects the vertical field of vision

# define NB_BUTTON 5
# define DEFAULT_BUTTON_COLOUR RED
# define PRESSED_BUTTON_COLOUR ORANGE
# define BUTTON_ADD_SECTOR 2

# define NB_SECT_MAX 50

//# include "/Users/user42/sdl/SDL2-2.0.8/include/SDL.h"

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

typedef struct			s_bmp_header_f
{
	int					type;
	int					size;
	uint16_t			reserved1;
	uint16_t			reserved2;
	int					offset;
	int					dib_header_size;
	int					width_px;
	int					height_px;
	int					num_planes;
	int					bits_per_pixel;
	int					compression;
	int					image_size_bytes;
	int					x_res;
	int					y_res;
	int					num_colors;
	int					important_colors;
	int					padding;
}						t_bmp_header_f;

typedef struct			s_bmp
{
	t_bmp_header_f		header;
	int					*data;
	int					nb;
}						t_bmp;

typedef struct			s_color
{
	int					off_r;
	int					off_b;
	int					off_g;
}						t_color;

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
typedef struct			s_menu
{
	int					on;
	int					gun_pointer;
	int					bot_level;
}						t_menu;

typedef struct			s_music
{
	int					mute;
	int					music;
	char*				name;
}						t_music;

typedef struct			s_inventory
{
	int					ammo;
	int					weapon_type[4];
	int					keys;
	int					shield;
	int					count;
	// int           grail;
}						t_inventory;

typedef struct			s_weapon
{
	int					anim;
	int					damage;
	// t_point         dir_shoot;
}						t_weapon;

typedef struct			s_anim
{
	int					started;
	// int           curr_anim_walk;
	int					curr_anim;
	// int           shoot;
}						t_anim;

typedef struct        s_line
{
    t_fpoint            orig;
    t_fpoint            end;
}                    t_line;
// typedef struct	s_player
// {
//     int	x;  // x pos of the Player
//     int	y;  // y pos of  the Player
//     int mv_speed; // mouvement speed of the Player
//     int rt_speed; // rotation speed of the camera for the Player
// }		t_player;

typedef struct			s_player
{
	struct xyz { float x,y,z; } where,      // Current position
	                            velocity;   // Current motion vector
	float				angle;
	float				anglesin;
	float				anglecos;
	float				yaw;   // Looking towards (and sin() and cos() thereof)
	unsigned			sector;                        // Which sector the player is currently in
	int					life;
	int					is_dead;
}						t_player;

typedef struct			s_sector
{
	float floor, ceil;
	struct xy { float x,y; } *vertex; // Each vertex has an x and y coordinate
	signed char			*neighbors;           // Each edge may have a corresponding neighboring sector
	unsigned			npoints;                 // How many vertexes there are
}						t_sector;

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
	t_point					orig;
	t_point					end;
	int					color;
	int					pressed;
	int					toggled;
}				t_button;

typedef struct			s_editor
{
	int					map_img_width;
	int					buttons_img_width;
	int					on;
	int 				sqr_size;
	int					off_x;
	int					off_y;
	int					old_x;
	int					old_y;
	void				*img_map;
	int					*data_map;
	void				*img_buttons;
	int					*data_buttons;
	int					endian;
	int					sl;
	int					bpp;
	int					closest_sector;
	int					closest_vertex;
	int					closest_sector2;
	int					closest_vertex2;
	t_fpoint			start;
	t_fpoint			end;
	t_button				buttons[NB_BUTTON];
	int					button_toggled;
}						t_editor;

typedef	struct 			s_event
{
	int 				but1;
	int 				new_sector;
}						t_event;

typedef	struct			s_mlx
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
	int					ducking;
	int					moving;
	unsigned			txty;
	t_menu				menu;
	t_music				music;
	t_weapon			weapon;
	t_inventory			inventory;
	t_anim				anim;
	t_tex				tex[6];
	t_bmp				*tab_anim[ANIM_NB];
	t_bmp				*tab_bmp[DIFF_BMP];
	t_editor			editor;
	t_point				mouse;
	t_fpoint			mouse_map;
	t_player			player;
	t_sector			*sectors;
	t_bham 				bham;
	t_event				events;
}						t_mlx;

struct Scaler
{
	int result, bop, fd, ca, cache;
};
/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */

//int key_press(int key, t_sdl *sdl);
//void erase_putback(t_sdl *sdl, t_player *player, t_sector *sectors, t_wall *walls);

/*
** BMP.C
*/

int						get_color(t_bmp *bmp, int x, int y);
t_bmp					*new_bmp(char *str);
int						check_tab_bmp(t_mlx *mlx);
int						read_color_vertical(t_bmp *bmp, int x, int y, unsigned char *data);

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

/*
** DRAW.C
*/

void					draw_screen(t_mlx *mlx);

/*
** EXPOSE.C
*/

int						expose(t_mlx *mlx);

/*
** FICHIER_DE_MERDE.C
*/

//RIP in pieces

/*
** GEOMETRY.C
*/

int			check_button_pressed(t_mlx *mlx);
int			is_inside(t_point p, t_button b);
t_fpoint                get_intersection(t_line line1, t_line line2, float slope1,
                            float slope2);
char                	check_valid_inter(t_fpoint inter, t_line line1, t_line line2);
float                	get_slope(t_line line);
float                	get_angle(t_fpoint p1, t_fpoint rel_dir);
float   			 	get_dist(t_fpoint p1, t_fpoint p2);
float    		get_dist_mouse_to_map(t_fpoint p1, struct xy p2);
float    		get_dist_map_to_map(struct xy p1, struct xy p2);
t_line			new_line(t_fpoint pos1, t_fpoint pos2);
t_fpoint		new_fpoint(float x, float y);
t_point			new_point(int x, int y);


/*
** HUD.C
*/

void					shoot_anim(t_mlx *mlx);
void					draw_ammo(t_mlx *mlx);
void					draw_shield(t_mlx *mlx);
void					draw_life_bar(t_mlx *mlx);
void					draw_weapon_hud(t_mlx *mlx);
void					draw_hud(t_mlx *mlx);

/*
** INIT.C
*/

void					init(t_mlx *mlx);

/*
** LOAD.C
*/

int						read_sector(int *k, struct xy *vert, char **split_line, t_mlx *mlx);
void					read_player(int n, char **split_line, t_mlx *mlx);
void					load_data(t_mlx *mlx);
void					load_texture(t_mlx *mlx);
void					unload_data(t_mlx *mlx);

/*
** MAP_EDITOR.C
*/

void					map_editor(t_mlx *mlx);
void					init_buttons(t_mlx *mlx);
void					toggle_button(t_mlx *mlx, int button);

/*
** MENU.C
*/

int						valid_pixel(int x, int y);
void					draw_image(t_point point, float zoom, t_bmp *bmp, t_mlx *mlx);
void					choose_level(t_mlx *mlx);
void					choose_music(t_mlx *mlx);
void					choose_music(t_mlx *mlx);
void					menu_strings(t_mlx *mlx);
void					menu_gun(t_mlx *mlx);
void					menu_gun2(t_mlx *mlx);
void					menu(t_mlx *mlx);
void					music(t_mlx *mlx);

/*
** MENU_KEYS.C
*/

void					enter_menu(t_mlx *mlx);
void					music_menu(int key, t_mlx *mlx);
void					switch_wepon(int key, t_mlx *mlx);
void					menu_key_hook(int key, t_mlx *mlx);

/*
** MOUSE_HOOK.C
*/

int						mouse_hook(int x, int y, t_mlx* mlx);
int						ft_key_hook(int key, t_mlx *mlx);
void					shoot_key(int key, int x, int y, t_mlx *mlx);
int						stop_movement(int key, t_mlx *mlx);
int                mouse_release(int key, int x, int y, t_mlx *mlx);

/*
** MOVE.C
*/

void					move_player(t_mlx *mlx, float dx, float dy);

/*
** SHAPE.C
*/

void					filled_rect(t_point size, int x, int y, t_mlx *mlx);
void					draw_rect(t_point size, int x, int y, t_mlx *mlx);
void					line(int x0, int y0, int x1, int y1, t_mlx *mlx);
void					draw_pixel(int x, int y, t_mlx *mlx);

/*
** TOOLS.C
*/

double					clamp(double a, double b, double c);
double					point_side(double px, double py, double x0, double y0, double x1, double y1);
int						intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
int						overlap(double a,double b,double c,double d);
double					vxs(double a, double b, double c, double d);
double					max(double a, double b);
double					min(double a, double b);
int						kill_mlx(char *message, t_mlx *mlx);
void					clear_img(int *data, int w, int h);
 
/*
** VLINE.C
*/

void					vline(int x, int y1,int y2, int top, int middle, int bottom, t_mlx *mlx);
int						Scaler_Next(struct Scaler *i);
struct Scaler			Scaler_Init(int a, int b, int c, int d, int f);


/*
** COMMENTED ?
*/

void					vline2(int x, int y1, int y2, struct Scaler ty, unsigned txtx, t_mlx *mlx);
int         check_tab_sprite(t_mlx *mlx);
/*
** BRESENHAM.C
*/
void	bresenham(t_mlx *mlx, int color);
void	dashed_bresenham(t_mlx *mlx, int color);



//struct xy	Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
#endif //DOOM_NUKEM_H
