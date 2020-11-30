#include "../include/doom_nukem.h"

t_line		new_line(t_fpoint pos1, t_fpoint pos2)
{
	t_line	line;

	line.orig.x = pos1.x;
	line.orig.y = pos1.y;
	line.end.x = pos2.x;
	line.end.y = pos2.y;
	return (line);
}

t_fpoint		new_fpoint(float x, float y)
{
	t_fpoint	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point		new_point(int x, int y)
{
	t_point	p;

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

float    get_dist(t_fpoint p1, t_fpoint p2)
{
    return ((float)sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
            (p2.y - p1.y) * (p2.y - p1.y)));
}
float    get_dist_mouse_to_map(t_fpoint p1, struct xy p2)
{
    return ((float)sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
            (p2.y - p1.y) * (p2.y - p1.y)));
}
float    get_dist_map_to_map(struct xy p1, struct xy p2)
{
    return ((float)sqrtf((p2.x - p1.x) * (p2.x - p1.x) +
            (p2.y - p1.y) * (p2.y - p1.y)));
}
float                get_angle(t_fpoint p1, t_fpoint rel_dir)
{
    t_fpoint            rel_pos;

    rel_pos.x = rel_dir.x - p1.x;
    rel_pos.y = p1.y - rel_dir.y;
    return (atan2f(rel_pos.y, rel_pos.x));
}

float                get_slope(t_line line)
{
    if (line.end.x != line.orig.x)
        return ((line.end.y - line.orig.y) / (line.end.x - line.orig.x));
    return (INFINITY);
}
char                check_valid_inter(t_fpoint inter, t_line line1, t_line line2)
{
    if (line1.orig.x < line1.end.x && (inter.x > line1.end.x ||
                inter.x < line1.orig.x))
        return (0);
    if (line1.orig.x > line1.end.x && (inter.x < line1.end.x ||
                inter.x > line1.orig.x))
        return (0);
    if (line1.orig.y < line1.end.y && (inter.y > line1.end.y ||
                inter.y < line1.orig.y))
        return (0);
    if (line1.orig.y > line1.end.y && (inter.y < line1.end.y ||
                inter.y > line1.orig.y))
        return (0);
    if (line2.orig.x < line2.end.x && (inter.x > line2.end.x ||
                inter.x < line2.orig.x))
        return (0);
    if (line2.orig.x > line2.end.x && (inter.x < line2.end.x ||
                inter.x > line2.orig.x))
        return (0);
    if (line2.orig.y < line2.end.y && (inter.y > line2.end.y ||
                inter.y < line2.orig.y))
        return (0);
    if (line2.orig.y > line2.end.y && (inter.y < line2.end.y ||
                inter.y > line2.orig.y))
        return (0);
    return (1);
}
t_fpoint                get_intersection(t_line line1, t_line line2, float slope1,
                            float slope2)
{
    t_fpoint         inter;
    float            c1;
    float            c2;

    c1 = line1.orig.y - slope1 * line1.orig.x;
    c2 = line2.orig.y - slope2 * line2.orig.x;
    if (slope1 == slope2)
    {
        inter.x = INFINITY;
        inter.y = INFINITY;
    }
    else if (isinf(slope1) && !isinf(slope2))
    {
        inter.x = line1.orig.x;
        inter.y = slope2 * inter.x + c2;
    }
    else if (!isinf(slope1) && isinf(slope2))
    {
        inter.x = line2.orig.x;
        inter.y = slope1 * inter.x + c1;
    }
    else
    {
        inter.x = (c2 - c1) / (slope1 - slope2);
        inter.y = slope1 * inter.x + c1;
    }
    if (slope1 * slope2 == -1)
    {
        inter.x = (c2 - c1) / (slope1 - slope2);
        inter.y = slope1 * inter.x + c1;
    }
    if (!check_valid_inter(inter, line1, line2))
    {
        inter.x = NAN;
        inter.y = NAN;
    }
    return (inter);
}
