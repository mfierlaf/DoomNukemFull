/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:58:48 by mfierlaf          #+#    #+#             */
/*   Updated: 2020/10/26 17:39:40 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/doom_nukem.h"
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
		vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
		vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

void draw_screen(t_mlx *mlx)
{
	unsigned x;
  unsigned n;

  x = -1;
  n = -1;
	enum { MaxQueue = 32 };  // maximum number of pending portal renders
	struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
	int ytop[W]= {0}, ybottom[W], renderedsectors[mlx->num_sectors];
	while (++x < W)
		ybottom[x] = H - 1;
	while (++n < mlx->num_sectors) renderedsectors[n] = 0; //glitch if while loop

	/* Begin whole-screen rendering from where the player is. */
	*head = (struct item) { mlx->player.sector, 0, W - 1 };
	if (++head == queue + MaxQueue) head = queue;
	do {
		/* Pick a sector & slice from the queue to draw */
		const struct item now = *tail;
		if(++tail == queue+MaxQueue) tail = queue;

		if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
		++renderedsectors[now.sectorno];
		t_sector* sect = &mlx->sectors[now.sectorno];
		/* Render each wall of this sector that is facing towards player. */
		// printf("TEST\n");
		for (unsigned s = 0; s < sect->npoints; ++s)
		{
			// printf("hello1\n");
			/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
			float vx1 = sect->vertex[s+0].x - mlx->player.where.x, vy1 = sect->vertex[s+0].y - mlx->player.where.y;
			float vx2 = sect->vertex[s+1].x - mlx->player.where.x, vy2 = sect->vertex[s+1].y - mlx->player.where.y;
			/* Rotate them around the player's view */
			// printf("hello2\n");
			float pcos = mlx->player.anglecos, psin = mlx->player.anglesin;

			float tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
			float tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
			/* Is the wall at least partially in front of the player? */
			//printf("tz1 = %f, tz2 = %f\n", tz1, tz2);
			if (tz1 <= 0 && tz2 <= 0) continue;
			/* If it's partially behind the player, clip it against player's view frustrum */
			// printf("hello3\n");
			if (tz1 <= 0 || tz2 <= 0)
			{
				float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
				// Find an intersection between the wall and the approximate edges of player's view
				struct xy i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
				struct xy i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
				if (tz1 < nearz)
				{
					if (i1.y > 0)
					{
						tx1 = i1.x;
						tz1 = i1.y;
					}
					else
					{
						tx1 = i2.x;
						tz1 = i2.y;
					}
				}
				if (tz2 < nearz)
				{
					if (i1.y > 0)
					{
						tx2 = i1.x;
						tz2 = i1.y;
					}
					else
					{
						tx2 = i2.x;
						tz2 = i2.y;
					}
				}
			}
			/* Do perspective transformation */
			float xscale1 = hfov / tz1, yscale1 = vfov / tz1;    int x1 = W/2 - (int)(tx1 * xscale1);
			float xscale2 = hfov / tz2, yscale2 = vfov / tz2;    int x2 = W/2 - (int)(tx2 * xscale2);
			if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
			/* Acquire the floor and ceiling heights, relative to where the player's view is */
			float yceil  = sect->ceil  - mlx->player.where.z;
			float yfloor = sect->floor - mlx->player.where.z;
			/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
			int neighbor = sect->neighbors[s];
			float nyceil = 0;
			float nyfloor = 0;
			if (neighbor >= 0) // Is another sector showing through this portal?
			{
				nyceil  = mlx->sectors[neighbor].ceil - mlx->player.where.z;
				nyfloor = mlx->sectors[neighbor].floor - mlx->player.where.z;
			}
			/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
#define Yaw(y,z) (y + z * mlx->player.yaw)
			int y1a  = H / 2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = H / 2 - (int)(Yaw(yfloor, tz1) * yscale1);
			int y2a  = H / 2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = H / 2 - (int)(Yaw(yfloor, tz2) * yscale2);
			/* The same for the neighboring sector */
			int ny1a = H / 2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = H / 2 - (int)(Yaw(nyfloor, tz1) * yscale1);
			int ny2a = H / 2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = H / 2 - (int)(Yaw(nyfloor, tz2) * yscale2);

			/* Render the wall. */
			int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);

			int x = beginx - 1;
			while (++x <= endx)
			{
				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
				int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

				/* Render ceiling: everything above this sector's ceiling height. */
			//	printf("1\n");
				vline(x, ytop[x], cya-1, 0x111111, 0x222222, 0x111111, mlx);
				//0x111111
				//0x222222
				//0x111111
				/* Render floor: everything below this sector's floor height. */
		//		printf("2\n");
				vline(x, cyb+1, ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF, mlx);
				//0x0000FF
				//0x0000AA
				//0x0000FF

				/* Is there another sector behind this edge? */
				if (neighbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
					int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
					/* If our ceiling is higher than their ceiling, render upper wall */
					unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);

					vline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0, mlx);
					// Between our and their ceiling
					//0
					//x==x1||x==x2 ? 0 : r1
					//0
					ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
					/* If our floor is lower than their floor, render bottom wall */

					vline(x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0, mlx); // Between their and our floor
					//0
					//x==x1||x==x2 ? 0 : r2
					//0
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else
				{
					/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
					unsigned r = 0x010101 * (255-z);
					vline(x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0, mlx);
					//0
					//x==x1||x==x2 ? 0 : r
					//0
				}
			}
			/* Schedule the neighboring sector for rendering within the window formed by this wall. */
			if (neighbor >= 0 && endx >= beginx && (head + MaxQueue + 1 - tail) % MaxQueue)
			{
				*head = (struct item) { neighbor, beginx, endx };
				if (++head == queue+MaxQueue) head = queue;
			}
		} // for s in sector's edges
		++renderedsectors[now.sectorno];
	}
	while (head != tail); // render any other queued sectors
}
