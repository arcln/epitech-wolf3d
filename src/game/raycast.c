/*
** raycast.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 09:41:32 2016 Arthur Chaloin
** Last update Tue Jan 10 13:52:14 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static t_wall		get_wall_info(t_ray		rays[2],
				      int		**map,
				      sfVector2i	size)
{
  t_wall		wall;

  if (rays[0].distance < rays[1].distance)
    {
      wall.distance = rays[0].distance;
      wall.side = 0;
      if (rays[0].pos.y < size.y && rays[0].pos.y > 0 &&
	  rays[0].pos.x < size.x && rays[0].pos.x > 0)
        wall.texture = map[rays[0].pos.y][rays[0].pos.x] - 2;
      else
	wall.texture = 0;
      wall.hit_pos = rays[0].fpos.y - trunc(rays[0].fpos.y);
    }
  else
    {
      wall.distance = rays[1].distance;
      wall.side = 1;
      if (rays[1].pos.y < size.y && rays[1].pos.y > 0 &&
	  rays[1].pos.x < size.x && rays[1].pos.x > 0)
        wall.texture = map[rays[1].pos.y][rays[1].pos.x] - 2;
      else
	wall.texture = 0;
      wall.hit_pos = rays[1].fpos.x - trunc(rays[1].fpos.x);
    }
  return (wall);
}

static sfVector2f	calibrate(sfVector2f	pos,
				  float		dir,
				  int		axis,
				  float		rad_dir)
{
  sfVector2f		raypos;

  if (axis)
    if (dir == 90 || dir == 270)
      raypos.x = -1;
    else
      {
	raypos.y = (dir > 90 && dir < 270) ?
	  ceil(pos.y) : trunc(pos.y);
	raypos.x = pos.x + ((dir > 180) ?
			    -(fabsf(pos.y - raypos.y) * tan(rad_dir)) :
			    (fabsf(pos.y - raypos.y) * tan(rad_dir)));
      }
  else
    if (dir == 0 || dir == 180)
      raypos.y = -1;
    else
      {
	raypos.x = (dir > 180) ? trunc(pos.x) : ceil(pos.x);
	raypos.y = pos.y + ((dir > 90 && dir < 270) ?
			    (fabsf(pos.x - raypos.x) * tan(rad_dir)) :
			    -(fabsf(pos.x - raypos.x) * tan(rad_dir)));
      }
  return (raypos);
}

static t_ray		throw_y(sfVector2f	pos,
				float		dir,
                                int		**map,
				sfVector2i	map_size)
{
  t_ray			ray;
  float			delta;
  float			rad_dir;
  sfVector2f		raypos;

  rad_dir = ((dir < 90) ? dir : (dir < 180) ? 180 - dir : (dir < 270) ?
	     dir - 180 : 360 - dir) * M_PI / 180.;
  raypos = calibrate(pos, dir, 1, rad_dir);
  if (raypos.x != -1)
    {
      ray.distance = sqrt(pow(raypos.x - pos.x, 2) + pow(raypos.y - pos.y, 2));
      delta = sqrt(1 + pow(tan(rad_dir), 2));
      raypos.y = (dir < 90 || dir > 270) ? raypos.y - 1 : raypos.y;
      while ((int)trunc(raypos.y) > 0 && (int)trunc(raypos.y) < map_size.y &&
	     (int)trunc(raypos.x) > 0 && (int)trunc(raypos.x) < map_size.x &&
	     map[(int)trunc(raypos.y)][(int)trunc(raypos.x)] < 2)
        {
          raypos.y += (dir > 90. && dir < 270.) ? 1 : -1;
          raypos.x += (dir > 180.) ? -tan(rad_dir) : tan(rad_dir);
          ray.distance += delta;
        }
      ray.pos.x = (int)trunc(raypos.x); ray.pos.y = (int)trunc(raypos.y);
      return (ray.fpos = raypos, ray);
    }
  return (ray.distance = 2147483647, ray);
}

static t_ray		throw_x(sfVector2f	pos,
				float		dir,
                                int		**map,
				sfVector2i	map_size)
{
  t_ray			ray;
  float			delta;
  float			rad_dir;
  sfVector2f		raypos;

  rad_dir = ((dir < 90.) ? 90 - dir : (dir < 180.) ? dir - 90 : (dir < 270.) ?
	     270 - dir : dir - 270) * M_PI / 180.;
  raypos = calibrate(pos, dir, 0, rad_dir);
  if (raypos.y == -1)
    return (ray.distance = 2147483647, ray);
  ray.distance = sqrt(pow(raypos.x - pos.x, 2) + pow(raypos.y - pos.y, 2));
  delta = sqrt(1 + pow(tan(rad_dir), 2));
  raypos.x = (dir > 180) ? raypos.x - 1 : raypos.x;
  while ((int)trunc(raypos.y) > 0 && (int)trunc(raypos.y) < map_size.y &&
	 (int)trunc(raypos.x) > 0 && (int)trunc(raypos.x) < map_size.x &&
	 map[(int)trunc(raypos.y)][(int)trunc(raypos.x)] < 2)
    {
      raypos.x += (dir > 180.) ? -1 : 1;
      raypos.y += (dir > 90. && dir < 270.) ?
	tan(rad_dir) : -tan(rad_dir);
      ray.distance += delta;
    }
  (ray.pos.x = (int)trunc(raypos.x)); (ray.pos.y = (int)trunc(raypos.y));
  return (ray.fpos = raypos, ray);
}

t_wall		raycast(sfVector2f	pos,
			float		dir,
			int		**map,
			sfVector2i	map_size)
{
  t_wall	wall;
  t_ray		rays[2];

  dir += 90;
  while (dir >= 360)
    dir -= 360;
  while (dir < 0)
    dir += 360;
  rays[0] = throw_x(pos, dir, map, map_size);
  rays[1] = throw_y(pos, dir, map, map_size);
  wall = get_wall_info(rays, map, map_size);
  return (wall);
}
