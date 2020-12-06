#include "../include/doom_nukem.h"

t_fpoint		new_fpoint(float x, float y)
{
	t_fpoint	p;

	p.x = x;
	p.y = y;
	return (p);
}

int	is_inside(t_point p, t_button b)
{
	if (p.x > b.orig.x && p.x < b.end.x && p.y > b.orig.y && p.y < b.end.y)
		return (1);
	return (0);
}

float	get_dist_mouse_to_map(t_fpoint p1, t_xy p2)
{
    return ((float)sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
            (p2.y - p1.y) * (p2.y - p1.y)));
}

float    get_dist_map_to_map(t_xy p1, t_xy p2)
{
    return ((float)sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
            (p2.y - p1.y) * (p2.y - p1.y)));
}
