/*
** display.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 11:09:04 2016 Arthur Chaloin
** Last update Sun Jan 15 18:56:37 2017 Arthur Chaloin
*/
#include "wolf3d.h"

void		update_fps(t_time *time, t_video *video)
{
  sfText_setString(video->fps, my_strcat("Score : ", my_strnbr(video->score)));
  time->frame_nb = 0;
  time->elapsed = 0;
}

void		display_kill(t_video *video)
{
  sfText	*text;
  sfFont	*font;
  int		size;

  if (video->kill < 3)
    size = 4 * video->kill;
  else if (video->kill < 6)
    size = 4 * (15 - video->kill);
  else
    size = 30;
  font = sfFont_createFromFile("fonts/BGB.ttf");
  text = sfText_create();
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, size);
  sfText_setColor(text, sfWhite);
  sfText_setString(text, (video->headshot) ? "+100\nHEADSHOT" : "+50");
  sfText_setPosition(text, create_vector((video->mode.width / 2) - (size / 2),
			(video->mode.height / 2) - (size / 2)));
  sfRenderWindow_drawText(video->window, text, NULL);
  sfText_destroy(text);
  sfFont_destroy(font);
  video->kill++;
  if (video->kill >= 21)
    video->kill = -1;
}

void		display(t_player *player, t_map *map, t_video *video)
{
  t_wall	wall;
  float		actual_angle;
  unsigned int	scan;

  scan = 0;
  actual_angle = player->dir - (video->fov / video->viser / 2.0);
  draw_sky(video);
  while (scan < video->mode.width)
    {
      wall = raycast(player->pos, actual_angle, map->map, map->size);
      draw(&wall, scan, video, actual_angle - player->dir);
      actual_angle = actual_angle + (video->fov / video->viser /
				     (float)video->mode.width);
      scan++;
    }
  draw_players(video, map, player);
  draw_minimap(video, map, player);
  sfTexture_updateFromPixels(video->texture, video->fb->pixels,
                             WIDTH, HEIGHT, 0, 0);
  sfRenderWindow_drawSprite(video->window, video->sprite, NULL);
  draw_weapon(video, player);
  sfRenderWindow_drawText(video->window, video->fps, NULL);
  if (video->kill != -1)
    display_kill(video);
}
