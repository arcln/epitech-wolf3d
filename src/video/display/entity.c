/*
** entity.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/video/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan 10 20:01:54 2017 Arthur Chaloin
** Last update Sun Jan 15 21:25:58 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static int	get_x_position(float direction, t_video *video)
{
  float		x_pos;
  float		player_dir;

  player_dir = video->player.dir;
  while (player_dir > 360.)
    player_dir -= 360.;
  while (player_dir < 0.)
    player_dir += 360.;
  x_pos = ((direction - player_dir) + (video->fov / video->viser / 2)) /
      ((float)video->fov / (float)video->viser);
  x_pos *= (float)video->mode.width;
  return (x_pos);
}

static void	draw_player_line(t_video *video,
		                 sfVector2i from,
			         sfVector2i to,
                                 float scan)
{
  double	img_y;
  double	img_x;
  sfVector2u	size;
  sfVector2i	origin;
  sfColor	color;

  origin = from;
  size = sfImage_getSize(video->player_sprite[0]);
  img_x = scan * (float)size.x;
  img_y = 0;
  if (from.y < 0)
    {
      from.y = 0;
      img_y += (float)size.y / fabsf(to.y - origin.y) * -origin.y;
    }
  while (from.y != to.y && (unsigned int)from.y <= video->mode.height)
    {
      color = sfImage_getPixel(video->player_sprite[0], img_x, round(img_y));
      if (color.a > 127)
        put_pixel(video->fb, from.x, from.y, color);
      from.y++;
      img_y += (float)size.y / fabsf(to.y - origin.y);
    }
}

int	is_visible(float distance, float direction,
			   t_map *map, t_video *video)
{
  t_wall	wall;

  wall = raycast(video->player.pos, direction, map->map, map->size);
  if (wall.distance < distance)
    return (0);
  return (1);
}

void		draw_player(t_map *map, float dist, float dir, t_video *video)
{
  int		scan, x_pos;
  float		final_angle, height, width;
  sfVector2u	size;
  sfVector2i	from, to;

  scan = 0;
  size = sfImage_getSize(video->player_sprite[0]);
  x_pos = get_x_position(dir, video);
  height = ((float)video->mode.height / dist) * ((float)video->viser / 2.);
  width = height * ((float)size.x / (float)size.y) * 2.;
  final_angle = ((float)video->fov / (float)video->viser /
		 (float)video->mode.width) * width;
  while ((unsigned int)scan < width)
    {
      from.x = x_pos + scan;
      to.x = x_pos + scan;
      from.y = ((float)video->mode.height / 2.) - height + (float)video->y_axis
	  + (84. * (video->viser == 4. && video->player.firing == 42.)) + 50;
      to.y = ((float)video->mode.height / 2.) + height + (float)video->y_axis +
	  (84. * (video->viser == 4. && video->player.firing == 42.)) + 50;
      if (is_visible(dist, dir, map, video))
	draw_player_line(video, from, to, (float)scan / width);
      dir += final_angle / width;
      scan++;
    }
}
