#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define UP_ARROW 65362
# define ESC 65307
# define SP 32
# define LCTRL 65507
# define W 1200
# define H 800
# define JUMP_SPEED 0.03f
# define SPEED 0.1f
# define EyeHeight  6    // Camera height from floor when standing
# define DuckHeight 2.5  // And when crouching
# define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
# define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
# define hfov (0.73f*H)  // Affects the horizontal field of vision
# define vfov (.2f*H)    // Affects the vertical field of vision
//# include "/Users/user42/sdl/SDL2-2.0.8/include/SDL.h"
# include "../minilibx_linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/incl/libft.h"
# include "keycode.h"

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

typedef	struct s_mlx
{
	void	*mlx;
	void	*win;
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

  t_point mouse;
	t_player  player;
	t_sector  *sectors;
}				t_mlx;

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */



//int key_press(int key, t_sdl *sdl);
//void erase_putback(t_sdl *sdl, t_player *player, t_sector *sectors, t_wall *walls);
// LOAD.C
void LoadData(t_mlx *ml);
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
//struct xy	Intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
#endif //DOOM_NUKEM_H
