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
	while (++n < mlx->num_sectors)
		renderedsectors[n] = 0;

	/* Begin whole-screen rendering from where the player is. */
	*head = (struct item) { mlx->player.sector, 0, W - 1 };
	if (++head == queue + MaxQueue) head = queue;
	do {
		/* Pick a sector & slice from the queue to draw */
		const struct item now = *tail;
		if (++tail == queue+MaxQueue) tail = queue;

		if (renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
		++renderedsectors[now.sectorno];
		t_sector* sect = &mlx->sectors[now.sectorno];
		/* Render each wall of this sector that is facing towards player. */
		// printf("TEST\n");
		for (unsigned s = 0; s < sect->npoints; ++s)
		{
			int u0 = 0;
			int u1 = TEXTURE_SIZE - 1;
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
			float xscale1 = (W * HFOV) / tz1, yscale1 = (H * VFOV) / tz1;    int x1 = W/2 - (int)(tx1 * xscale1);
			float xscale2 = (W * HFOV) / tz2, yscale2 = (H * VFOV) / tz2;    int x2 = W/2 - (int)(tx2 * xscale2);
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
			struct Scaler ya_int = Scaler_Init(x1,beginx,x2, y1a,y2a);
            struct Scaler yb_int = Scaler_Init(x1,beginx,x2, y1b,y2b);
            



      //       void OMP_SCALER_LOOP_BEGIN(a, b, c, d, e, f)
      //       {
    		// 	struct Scaler e##int = Scaler_Init(a, a, (c)-1, (d) * 32768, (f) * 32768);
    		// 	for (int b = (a); b < (c); ++b)
    		// 	{ 
		    //     	float e = Scaler_Next(&e##int) / 32768.f;
   			// 	}
   			// }


		    
			while (++x <= endx)
			{
				//TEXTURE MAPPING TEST
				int txtx = (u0*((x2-x)*tz2) + u1*((x-x1)*tz1)) / ((x2-x)*tz2 + (x-x1)*tz1);
				//TEXTURE MAPPING TEST

				/* Calculate the Z coordinate for this point. (Only used for lighting.) */
				int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
				/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
				int ya = Scaler_Next(&ya_int);
                int yb = Scaler_Next(&yb_int);

				int cya = clamp(ya, ytop[x],ybottom[x]); // top
				int cyb = clamp(yb, ytop[x],ybottom[x]); // bottom
				//TEXTURE MAPPING TEST
				#define CeilingFloorScreenCoordinatesToMapCoordinates(mapY, screenX,screenY, X,Z) \
                    do { Z = (mapY)*H*VFOV / ((H/2 - (screenY)) - mlx->player.yaw *H*VFOV); \
                         X = (Z) * (W/2 - (screenX)) / (W*HFOV); \
                         RelativeMapCoordinatesToAbsoluteOnes(X,Z); } while(0)
                //
                #define RelativeMapCoordinatesToAbsoluteOnes(X,Z) \
                    do { float rtx = (Z) * pcos + (X) * psin; \
                         float rtz = (Z) * psin - (X) * pcos; \
                         X = rtx + mlx->player.where.x; Z = rtz + mlx->player.where.y; \
                    } while(0)
                for (int y=ytop[x]; y<=ybottom[x]; ++y)
                {
                    if(y >= cya && y <= cyb)
                    {
                    	y = cyb;
                    	continue;
                    }
                    float hei = y < cya ? yceil : yfloor;
                    float mapx;
                    float mapz;
                    CeilingFloorScreenCoordinatesToMapCoordinates(hei, x,y,  mapx,mapz);
                    unsigned txtx = (mapx * 16), txtz = (mapz * 16);
                    mlx->tex->tex_ternary = y < cya ? mlx->tex[2].data : mlx->tex[1].data;
                    mlx->data[y * W + x] = mlx->tex->tex_ternary[(txtx % TEXTURE_SIZE)* TEXTURE_SIZE + (txtz % TEXTURE_SIZE)];

                    //TODO EN BMP!!
                    // int color = get_color(mlx->tab_bmp[0], (txtx % TEXTURE_SIZE), (mlx->txty % TEXTURE_SIZE));
      				// if (color != FILTER_COLOR)
        		// 		mlx->data[y * W + x] = color;
                }
                //TEXTURE MAPPING TEST

				/* Is there another sector behind this edge? */
				if (neighbor >= 0)
				{
					/* Same for _their_ floor and ceiling */
					int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a;
					int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b;
					int cnya = clamp(nya, ytop[x],ybottom[x]);
					int cnyb = clamp(nyb, ytop[x],ybottom[x]);

                	//TEXTURE MAPPING TEST
					// vline2(x, cya, cnya-1, (struct Scaler)Scaler_Init(ya,cya,yb, 0, TEXTURE_SIZE - 1), txtx, mlx);
					vertical_line(x, cya, cnya-1, (struct Scaler)Scaler_Init(ya,cya,yb, 0, TEXTURE_SIZE - 1), txtx, mlx);
					//TEXTURE MAPPING TEST

					/* If our ceiling is higher than their ceiling, render upper wall */
					// unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8); //NO TEXTURES
					// vline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0, mlx); //NO TEXTURES
					// Between our and their ceiling
					//0
					//x==x1||x==x2 ? 0 : r1
					//0
					ytop[x] = clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
					/* If our floor is lower than their floor, render bottom wall */

					//TEXTURE MAPPING TEST
					vertical_line(x, cnyb+1, cyb, (struct Scaler)Scaler_Init(ya,cnyb+1,yb, 0, TEXTURE_SIZE - 1), txtx, mlx);
					//TEXTURE MAPPING TEST

					// Between their and our floor
					//0
					//x==x1||x==x2 ? 0 : r2
					//0
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
				}
				else
				{
					//TEXTURE MAPPING TEST
					vertical_line(x, cya,cyb, (struct Scaler)Scaler_Init(ya,cya,yb, 0, TEXTURE_SIZE - 1), txtx, mlx);
					//TEXTURE MAPPING TEST

					/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
					// unsigned r = 0x010101 * (255-z);  //NO TEXTURES
					// vline(x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0, mlx);  //NO TEXTURES
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
