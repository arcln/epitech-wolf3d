/*
** view.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/video/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan 10 13:13:21 2017 Arthur Chaloin
** Last update Tue Jan 10 16:46:32 2017 Arthur Chaloin
*/
#include "wolf3d.h"

void		draw_sky(t_video *video)
{
  sfVector2f	pos;

  if (video->skypos.x > 0)
    video->skypos.x -= 1920;
  else if (video->skypos.x < -1920)
    video->skypos.x += 1920;
  draw_image(video->sky, video->skypos, video, 0);
  pos.x = video->skypos.x + 1920;
  pos.y = -420;
  draw_image(video->sky, pos, video, 0);
}

void	draw(t_wall *wall, unsigned int scan, t_video *video, float a)
{
  int		line_len;
  sfVector2i	from;
  sfVector2i	to;

  wall->distance *= cos(a * M_PI / 180);
  line_len = ((float)video->mode.height / wall->distance) * video->viser
      - abs(video->y_axis / 42);
  from.x = scan;
  from.y = video->mode.height;
  to.x = scan;
  to.y = line_len / 2.0 + (float)video->mode.height / 2.0 - 1 + video->y_axis +
      (84 * (video->viser == 4 && video->player.firing == 42));
  draw_line(video->fb, from, to, create_color(50, 50, 50));
  to.y += 1;
  from.y = -line_len / 2.0 + (float)video->mode.height / 2.0 + video->y_axis +
      (84 * (video->viser == 4 && video->player.firing == 42));
  draw_texture(video, from, to, wall);
}
