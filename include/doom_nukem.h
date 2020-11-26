#ifndef DOOM_NUKEM_H

# define DOOM_NUKEM_H

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
# define ENTR_LN 65293
# define K1_LN 38
# define K2_LN 233
# define K3_LN 34
# define K4_LN 39
# define K5_LN 40

# define NB_OBJ 1
# define DIFF_BMP 48
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
# define SLICE ((HFOV * 2) / W)
# define M_PI 3.14159265359
//# include "/Users/user42/sdl/SDL2-2.0.8/include/SDL.h"
// # include "../minilibx_linux/mlx.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/incl/libft.h"
# include "keycode.h"
# include <stdint.h>
# include <fcntl.h>

typedef struct        s_bmp_header
{
  uint16_t        type;
  uint16_t        size_1;
  uint16_t        size_2;
  uint16_t        reserved1;
  uint16_t        reserved2;
  uint16_t        offset1;
  uint16_t        offset2;
  uint16_t        dib_header_size1;
  uint16_t        dib_header_size2;
  int16_t         width_px1;
  int16_t         width_px2;
  int16_t         height_px1;
  int16_t         height_px2;
  uint16_t        num_planes;
  uint16_t        bits_per_pixel;
  uint16_t        compression1;
  uint16_t        compression2;
  uint16_t        image_size_bytes1;
  uint16_t        image_size_bytes2;
  int16_t         x_resolution_ppm1;
  int16_t         x_resolution_ppm2;
  int16_t         y_resolution_ppm1;
  int16_t         y_resolution_ppm2;
  uint16_t        num_colors1;
  uint16_t        num_colors2;
  uint16_t        important_colors1;
  uint16_t        important_colors2;
}             t_bmp_header;

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

typedef struct        s_pos
{
  float x;
  float y;
  float z;
}                     t_pos;

typedef struct s_point  {
  int x;
  int y;
}               t_point;

typedef struct s_line
{
  t_pos  orig;
  t_pos  end;
}             t_line;

typedef struct s_menu  {
  int on;
  int gun_pointer;
  int bot_level;
}               t_menu;

typedef struct        s_obj
{
  unsigned int  sector;
  int           tex;
  int           lootable;
  t_pos         pos;
  t_line        sprite_line;
  int           order;
  float         distance;
  int           life;
  int           isbot;
  int           initial_tex;
  int           nb_anim_walk;
  int           nb_anim;
}               t_obj;

typedef struct s_music  {
  int           mute;
  int           music;
  char*         name;
}               t_music;

typedef struct  s_inventory
{
  int           ammo;
  int           weapon_type[4];
  int           keys;
  int           shield;
  int           count;
  // int           grail;
}             t_inventory;

typedef struct  s_weapon
{
  int           anim;
  int           damage;
  // t_point         dir_shoot;
}             t_weapon;

typedef struct        s_sleep
{
  int           walk;
  int           shoot;
  int           death;
}             t_sleep;

typedef struct        s_anim
{
  int           started;
  int           curr_anim_walk;
  int           curr_anim;
  int           shoot;
}             t_anim;


// typedef struct	s_player
// {
//     int	x;  // x pos of the Player
//     int	y;  // y pos of  the Player
//     int mv_speed; // mouvement speed of the Player
//     int rt_speed; // rotation speed of the camera for the Player
// }		t_player;


typedef struct s_player
{
    struct xyz { float x,y,z; } where,      // Current position
                                velocity;   // Current motion vector
    float angle;
    float anglesin;
    float anglecos;
    float yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned sector;                        // Which sector the player is currently in
    int           life;
    int           is_dead;
    t_pos         dir;
    t_pos         old_dir;
} t_player;

typedef struct s_sector
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned npoints;                 // How many vertexes there are
} t_sector;

typedef struct    s_tex
{
    void        *img;
    int         *data;
    int         bpp;
    int         sl;
    int         endian;
    int         *tex_ternary;  
}                t_tex;

typedef struct s_editor
{
    int         map_img_width;
    int         on;
    void        *img;
    int         *data;
    int   endian;
    int   sl;
    int   bpp;
}               t_editor;

struct item
{
  int sectorno;
  int sx1;
  int sx2;
};

struct Scaler
{
  int result;
  int bop;
  int fd;
  int ca;
  int cache;
};

typedef struct s_draw 
{
  float mapx;
  float mapz;
  int neighbor;
  int y2a;
  int y1a;
  int y1b;
  int y2b;
  int ny1a;
  int ny2a;
  int ny1b;
  int ny2b;
  float pcos;
  float psin;
  float yceil;
  float yfloor;
  int ytop[W];
  int ybottom[W];
  struct Scaler ya_int;
  struct Scaler yb_int;
  int x1;
  int x2;
  float tz1;
  float tz2;
  int u1;
  int u0;
  int endx;
  int beginx;
  int txtx;
  int z;
  int ya;
  int yb;
  int cya;
  int cyb;
  float tx1;
  float tx2;
  struct item now;
  t_sector* sect;
  int check;
  int MaxQueue;
  struct item queue[32];
  struct item *head;
  struct item *tail;
  int *renderedsectors;
  struct xy i1;
  struct xy i2;
  float nearz;
  float yscale1;
  float yscale2;
  float mapy;
  int nya;
  int nyb;
  int cnya;
}               t_draw;

typedef	struct s_mlx
{
	void   *mlx;
	void   *win;
	void	*img;
	int		*data;
	int		endian;
	int		sl;
	int		bpp;
	int		color;
  unsigned int num_sectors;
  int     wasd[4];
  int     ground;
  int     falling;
  int     ducking;
  int     moving;
  unsigned txty;
  t_menu  menu;
  t_music music;
  t_weapon weapon;
  t_inventory inventory;
  t_anim anim;
  t_sleep sleep;
  t_tex   tex[6];
  t_bmp *tab_anim[ANIM_NB];
  t_bmp   *tab_bmp[DIFF_BMP];
  t_obj   objects[NB_OBJ];

  t_editor editor;
  t_point mouse;
	t_player  player;
	t_sector  *sectors;
}				t_mlx;


/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */



//int key_press(int key, t_sdl *sdl);
//void erase_putback(t_sdl *sdl, t_player *player, t_sector *sectors, t_wall *walls);
// LOAD.C
void LoadData(t_mlx *ml);
void load_texture(t_mlx *mlx);
void UnloadData(t_mlx *mlx);
// MOVE.C
void move_player(t_mlx *mlx, float dx, float dy);
// MOUSE_HOOK.C
int mouse_hook(int x, int y, t_mlx* mlx);
int ft_key_hook(int key, t_mlx *mlx);
int stop_movement(int key, t_mlx *mlx);
// VLINE.C
void vline(int x, int y1,int y2, int top, int middle, int bottom, t_mlx *mlx);
// DRAW.C
void draw_screen(t_mlx *mlx);
void  drawing(t_mlx *mlx, t_draw *draw);
void  boucle_drawing(t_mlx *mlx, t_draw *draw, int x);
void  draw_vline(t_mlx *mlx, t_draw *draw, int x);
void  check_edge(t_mlx *mlx, t_draw *draw);
int perspective(t_mlx *mlx, t_draw *draw, int s);
void  players_view_tz2(t_mlx *mlx, t_draw *draw);
void  players_view(t_mlx *mlx, t_draw *draw);
void  behind_player(t_mlx *mlx, t_draw *draw);
void  render(t_mlx *mlx, t_draw *draw);
void render_declaration(t_mlx *mlx, t_draw *draw, int s);
void draw_start(t_mlx *mlx, t_draw *draw);
// TOOLS.C
double	clamp(double a, double b, double c);
double	point_side(double px, double py, double x0, double y0, double x1, double y1);
int		intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
int		overlap(double a,double b,double c,double d);
float	vxs(float a, float b, float c, float d);
double	max(double a, double b);
double	min(double a, double b);
void 	clear_img(t_mlx *mlx);
int kill_mlx(char *message, t_mlx *mlx);
float Yaw(float y, float z, t_mlx *mlx);
struct xy Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
t_pos       new_pos(float x, float y);
t_line        new_line(t_pos orig, t_pos end);
t_pos       get_intersection(t_line line1, t_line line2, float slope1, float slope2);
char        check_valid_inter(t_pos inter, t_line line1, t_line line2);
float       get_slope(t_line line);
float get_dist(t_pos p1, t_pos p2);
float       get_angle(t_pos p1, t_pos rel_dir);
int       valid_pixel(int x, int y);
// EXPOSE.C
int expose(t_mlx *mlx);
// INIT.C
void init(t_mlx *mlx);
void    sprite_var(int sprite, t_mlx *mlx);
int Scaler_Next(struct Scaler *i);
void vline2(int x, int y1, int y2, struct Scaler ty, unsigned txtx, t_mlx *mlx);
struct Scaler Scaler_Init(int a, int b, int c, int d, int f);
int         get_color(t_bmp *bmp, int x, int y);
t_bmp       *new_bmp(char *str);
t_bmp         *read_header_bmp(char *file);
t_bmp         *read_img_bmp(char *file, t_bmp_header_f header);
int           convert_to_32(uint16_t left, uint16_t right);
t_bmp_header_f      convert_to_header(t_bmp_header src);
int         check_tab_bmp(t_mlx *mlx);
int         read_color_vertical(t_bmp *bmp, int x, int y, unsigned char *data);
int         check_tab_sprite(t_mlx *mlx);
void        *free_bmp(t_bmp *bmp, int *data, unsigned char *tmp);
void         menu(t_mlx *mlx);
void      draw_image(t_point point, float zoom, t_bmp *bmp, t_mlx *mlx);
void    menu_key_hook(int key, t_mlx *mlx);
void    menu_strings(t_mlx *mlx);
void    music(t_mlx *mlx);
void      filled_rect(t_point size, int x, int y, t_mlx *mlx);
void      draw_rect(t_point size, int x, int y, t_mlx *mlx);
void      line(int x0, int y0, int x1, int y1, t_mlx *mlx);
void      draw_pixel(int x, int y, t_mlx *mlx);
void      draw_hud(t_mlx *mlx);
void      shoot_key(int key, int x, int y, t_mlx *mlx);
//SPRITES.C
void draw_sprites(int x, t_mlx *mlx);
void                vertical_sprite_lines(t_mlx *mlx, int x, t_pos sp_orig,
    t_pos sp_end, int draw_start, int draw_end, t_pos inter, t_bmp *curr_bmp);
// BOTS.C
void        bot(int sprite, t_mlx *mlx);
// ANIM.C
void        shoot_anim(t_mlx *mlx);
void        sprite_anim_death(int sprite, t_mlx *mlx);
void        sprite_anim_walk(int sprite, t_mlx *mlx);


//struct xy	Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
#endif //DOOM_NUKEM_H
