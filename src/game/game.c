/*
** game.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Dec 27 13:45:57 2016 Arthur Chaloin
** Last update Sun Jan 15 18:45:04 2017 Arthur Chaloin
*/
#include "wolf3d.h"

sfVector2f		get_start(t_map *map)
{
  int			index;
  int			index2;
  sfVector2f		pos;

  index = 0;
  index2 = 0;
  while (index < map->size.y)
    {
      while (index2 < map->size.x)
	{
	  if (map->map[index][index2] == 0)
	    {
	      pos.x = (float)index2 + 0.5;
	      pos.y = (float)index + 0.5;
	    }
	  index2++;
	}
      index2 = 0;
      index++;
    }
  return (pos);
}

static void		init_loop(t_video *video, t_time *time, t_map *map)
{
  time->frame = sfClock_create();
  time->elapsed = 0;
  time->frame_nb = 0;
  time->total_frames = 0;
  video->time = time;
  video->player.dir = DEFAULT_DIR;
  video->player.pos = get_start(map);
  video->player.weapon = 2;
  video->player.firing = 0;
  init_pnj(video, map);
}

static void	handle_time(t_time *time, t_video *video)
{
  time->frame_nb++;
  time->total_frames++;
  time->elapsed += sfClock_getElapsedTime(time->frame).microseconds;
  if (time->elapsed > 1000000)
    update_fps(time, video);
}

static void	refresh_screen(t_video *video, t_player *player, t_map *map)
{
  sfRenderWindow_clear(video->window, sfBlack);
  clear(video);
  display(player, map, video);
  sfRenderWindow_display(video->window);
}

void		game_loop(t_video *video, t_map *map, t_keys *keys)
{
  int		is_open;
  t_time	time;

  is_open = 1;
  init_loop(video, &time, map);
  sfRenderWindow_setMouseCursorVisible(video->window, sfFalse);
  sfMusic_play(video->music);
  sfMusic_setLoop(video->music, 1);
  while (is_open)
    {
      handle_time(video->time, video);
      if (sfClock_getElapsedTime(video->time->frame).microseconds > FRAMETIME)
	{
          action(&video->player, keys, map, video);
	  if (handle_pnj(video, map))
	    dead(video, map);
	  refresh_screen(video, &video->player, map);
          sfClock_restart(video->time->frame);
	}
      is_open = handle_events(video, keys);
    }
  sfRenderWindow_setMouseCursorVisible(video->window, sfTrue);
  sfMusic_stop(video->music);
  sfMusic_stop(video->shot);
}
