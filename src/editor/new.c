/*
** new.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/editor/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Thu Jan  5 19:58:18 2017 Arthur Chaloin
** Last update Sun Jan 15 18:09:20 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	update_text(char *text, char new)
{
  if ((new >= 'a' && new <= 'z') || (new >= 'A' && new <= 'Z') ||
      (new >= '0' && new <= '9') || new == '.' || new == ' ')
    {
      text[my_strlen(text) + 1] = 0;
      text[my_strlen(text)] = new;
    }
  else
    text[my_strlen(text) - 1] = 0;
}

static void	display_options(t_video *video, sfVector2f cursor, t_map *map)
{
  sfVector2f	pos;

  pos.x = 370;
  pos.y = 320;
  draw_image(video->background, create_vector(0, 0), video, 0);
  draw_white_text("Map name", 42, pos, video, "fonts/default.ttf");
  pos.y = 420;
  draw_white_text("Map width", 42, pos, video, "fonts/default.ttf");
  pos.y = 520;
  draw_white_text("Map height", 42, pos, video, "fonts/default.ttf");
  draw_white_text(">", 42, cursor, video, "fonts/default.ttf");
  if (map->name)
    draw_white_text(map->name, 42, create_vector(600, 320),
	      video, "fonts/default.ttf");
  if (map->size.x)
    draw_white_text(my_strnbr(map->size.x), 42, create_vector(600, 420),
	      video, "fonts/default.ttf");
  if (map->size.y)
    draw_white_text(my_strnbr(map->size.y), 42, create_vector(600, 520),
	      video, "fonts/default.ttf");
}

static char	*get_text(t_video *video, sfVector2f *cursor, t_map *map)
{
  char		text[4096];

  text[0] = '\0';
  while (1)
    {
      clear(video);
      sfRenderWindow_clear(video->window, sfBlack);
      display_options(video, *cursor, map);
      draw_white_text(text, 42, create_vector(600, cursor->y), video, FONT);
      sfRenderWindow_display(video->window);
      while (sfRenderWindow_pollEvent(video->window, &(video->event)))
	{
	  if (video->event.type == sfEvtClosed)
	    exit(0);
	  else if (video->event.type == sfEvtKeyPressed &&
	      video->event.key.code == sfKeyReturn)
	    return (my_strdup(text));
	  else if (video->event.type == sfEvtKeyPressed &&
	      video->event.key.code == sfKeyDelete)
	    update_text(text, 0);
	  else if (video->event.type == sfEvtTextEntered)
	    update_text(text, video->event.text.unicode);
	}
      usleep(10000);
    }
}

static int	**generate_empty_map(sfVector2i size)
{
  int		index;
  int		index2;
  int		**map;

  index = 0;
  if (!(map = malloc(sizeof(int *) * (size.y + 1))))
    exit(84);
  while (index < size.y)
    {
      index2 = 0;
      if (!(map[index] = malloc(sizeof(int) * (size.x + 1))))
	exit(84);
      while (index2 < size.x)
	{
	  map[index][index2] = 0;
	  index2++;
	}
      index++;
    }
  return (map);
}

t_map		*new_map(t_video *video)
{
  t_map		*map;
  sfVector2f	cursor;

  cursor.x = 100;
  cursor.y = 320;
  if (!(map = malloc(sizeof(t_map))))
    exit(84);
  map->name = NULL;
  map->size.x = 0;
  map->size.y = 0;
  map->name = get_text(video, &cursor, map);
  cursor.y += 100;
  map->size.x = my_getnbr(get_text(video, &cursor, map));
  cursor.y += 100;
  map->size.y = my_getnbr(get_text(video, &cursor, map));
  map->map = generate_empty_map(map->size);
  return (map);
}
