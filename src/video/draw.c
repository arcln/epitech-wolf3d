/*
** my_draw_line.c for bswireframe in /home/arthur/Documents/B1-C Graphical Prog/bswireframe/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Thu Nov 17 15:56:22 2016 Arthur Chaloin
** Last update Sat Mar 18 15:44:35 2017 Arthur Chaloin
*/
#include "wolf3d.h"

void	clear(t_video *video)
{
  memset(video->fb->pixels, 42, video->mode.width * video->mode.height * 4);
}

inline void	put_pixel(t_my_framebuffer *fb,
		          int x, int y, sfColor color)
{
  unsigned int	*pixel;

  if (x < 0 || y < 0 || x >= fb->width || y >= fb->height)
    return;
  pixel = (void *)&(fb->pixels[(fb->width * y + x) * 4]);
  *pixel = (color.a << 24) + (color.b << 16) + (color.g << 8) + color.r;
}

void		draw_square(t_my_framebuffer *fb, sfVector2i pos,
			    int size, sfColor color)
{
  int		index;
  int		index2;

  index = 0;
  index2 = 0;
  while (index < size)
    {
      while (index2 < size)
	{
	  put_pixel(fb, pos.x + index2, pos.y + index, color);
	  index2++;
	}
      index2 = 0;
      index++;
    }
}

void		draw_true_line(t_my_framebuffer *framebuff,
			       sfVector2i from_int,
			       sfVector2i to,
			       sfColor color)
{
  double	norm;
  sfVector2f	dir;
  sfVector2f	from;

  from.x = (float)from_int.x;
  from.y = (float)from_int.y;
  dir.x = to.x - from.x;
  dir.y = to.y - from.y;
  norm = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
  dir.x /= (float)norm;
  dir.y /= (float)norm;
  while ((int)from.x != (int)to.x || (int)from.y != (int)to.y)
    {
      put_pixel(framebuff, from.x, from.y, color);
      if ((int)from.x != (int)to.x)
	from.x += dir.x;
      if ((int)from.y != (int)to.y)
	from.y += dir.y;
    }
  put_pixel(framebuff, from.x, from.y, color);
}

void		draw_line(t_my_framebuffer *framebuff,
			     sfVector2i from,
			     sfVector2i to,
			     sfColor color)
{
  if (to.y >= from.y)
    return;
  while (from.y != to.y)
    {
      put_pixel(framebuff, from.x, from.y, color);
      from.y += (from.y < to.y) ? 1 : -1;
    }
}
