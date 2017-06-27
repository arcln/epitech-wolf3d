/*
** editor.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/editor/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Thu Jan  5 15:01:25 2017 Arthur Chaloin
** Last update Tue Jan 10 12:57:18 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	update_map(t_map *map, sfVector2i mouse,
			   int texture, t_video *video)
{
  int		size;

  mouse.x -= 50;
  mouse.y -= 50;
  size = MIN((video->mode.width - 300.) / map->size.x,
	     (video->mode.height - 100.) / map->size.y);
  if (mouse.y / size < 0 ||
      mouse.y / size >= map->size.y ||
      mouse.x / size < 0 ||
      mouse.x / size >= map->size.x)
    return;
  map->map[mouse.y / size][mouse.x / size] = texture;
}

static int	get_texture_nb(sfImage **tab)
{
  int		count;

  count = 0;
  while (tab[count])
    count++;
  return (count);
}

static int	get_events(t_video *video, t_map *map,
			   t_keys *keys, int *actual)
{
  while (sfRenderWindow_pollEvent(video->window, &(video->event)))
    {
      if (video->event.type == sfEvtClosed ||
          (video->event.type == sfEvtKeyPressed &&
           video->event.key.code == sfKeyEscape))
        return (1);
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyReturn)
        return (save(map));
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyZ)
        *actual = (*actual) ? *actual - 1 : *actual;
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyS)
        *actual = (*actual < get_texture_nb(video->textures) - 1) ?
          *actual + 1 : *actual;
      if (video->event.type == sfEvtKeyPressed ||
          video->event.type == sfEvtMouseButtonPressed)
        set_keys_press(video, keys);
      if (video->event.type == sfEvtKeyReleased ||
          video->event.type == sfEvtMouseButtonReleased)
        set_keys_release(video, keys);
    }
  return (0);
}

static void	edit(t_map *map, t_video *video, t_keys *keys)
{
  int		actual;

  actual = 0;
  while (1)
    {
      clear(video);
      sfRenderWindow_clear(video->window, sfBlack);
      display_map(map, video);
      display_textures(video, actual);
      sfTexture_updateFromPixels(video->texture, video->fb->pixels,
                                 WIDTH, HEIGHT, 0, 0);
      sfRenderWindow_drawSprite(video->window, video->sprite, NULL);
      sfRenderWindow_display(video->window);
      if (get_events(video, map, keys, &actual))
	return;
      if (keys->left_mouse)
	update_map(map, sfMouse_getPosition((const sfWindow *)video->window),
		   actual + 2, video);
      if (keys->right_mouse)
	update_map(map, sfMouse_getPosition((const sfWindow *)video->window),
		   0, video);
      usleep(10000);
    }
}

void		editor(t_video *video, char *raw_map, t_keys *keys)
{
  t_map		*map;

  if (!strcmp(raw_map, "maps/_NEWMAP"))
    map = new_map(video);
  else
    map = load_map(raw_map);
  edit(map, video, keys);
}
