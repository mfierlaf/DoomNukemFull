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

# define DIFF_BMP 1
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
# define hfov (0.73f*H)  // Affects the horizontal field of vision
# define vfov (0.2f*H)    // Affects the vertical field of vision
//# include "/Users/user42/sdl/SDL2-2.0.8/include/SDL.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/incl/libft.h"
# include "keycode.h"
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


typedef struct s_point  {
    int x;
    int y;
}               t_point;

// typedef struct	s_player
// {
//     int	x;  // x pos of the Player
//     int	y;  // y pos of  the Player
//     int mv_speed; // mouvement speed of the Player
//     int rt_speed; // rotation speed of the camera for the Player
// }		t_player;

/*typedef	struct	s_sdl {
    void *sdl;
    SDL_Window *window;
    SDL_Renderer *renderer;
    t_player  *player; // Added for mlx use
    t_sector  *sectors; // Added for mlx use
    t_wall    *walls; // Added for mlx use
} t_sdl;*/

typedef struct s_player
{
    struct xyz { float x,y,z; } where,      // Current position
                                velocity;   // Current motion vector
    float angle;
    float anglesin;
    float anglecos;
    float yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned sector;                        // Which sector the player is currently in
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
  t_tex   tex[6];
  t_bmp   *tab_bmp[1];

  t_point mouse;
	t_player  player;
	t_sector  *sectors;
}				t_mlx;

struct Scaler { int result, bop, fd, ca, cache; };
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
// TOOLS.C
double	clamp(double a, double b, double c);
double	point_side(double px, double py, double x0, double y0, double x1, double y1);
int		intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
int		overlap(double a,double b,double c,double d);
double	vxs(double a, double b, double c, double d);
double	max(double a, double b);
double	min(double a, double b);
void 	clear_img(t_mlx *mlx);
int kill_mlx(t_mlx *mlx);
// EXPOSE.C
int expose(t_mlx *mlx);
// INIT.C
void init(t_mlx *mlx);
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

//struct xy	Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
#endif //DOOM_NUKEM_H