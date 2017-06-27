/*
** menu.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Dec 27 14:51:12 2016 Arthur Chaloin
** Last update Sun Jan 15 19:02:27 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	display_options(t_video *video, sfVector2f cursor)
{
  sfVector2f	pos;

  pos.x = 420;
  pos.y = 350;
  draw_white_text("Play", 42, pos, video, "fonts/default.ttf");
  pos.y = 450;
  draw_white_text("Editor", 42, pos, video, "fonts/default.ttf");
  pos.y = 550;
  draw_white_text("Quit", 42, pos, video, "fonts/default.ttf");
  draw_white_text(">", 42, cursor, video, "fonts/default.ttf");
}

static int	get_entry(t_video *video,
			  sfVector2f background_pos, sfVector2f *cursor)
{
  clear(video);
  sfRenderWindow_clear(video->window, sfBlack);
  draw_image(video->background, background_pos, video, 0);
  display_options(video, *cursor);
  sfRenderWindow_display(video->window);
  while (sfRenderWindow_pollEvent(video->window, &(video->event)))
    {
      if (video->event.type == sfEvtClosed ||
          (video->event.type == sfEvtKeyPressed &&
           video->event.key.code == sfKeyEscape))
        exit(0);
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyDown)
        (*cursor).y += ((*cursor).y == 550) ? -200 : 100;
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyUp)
        (*cursor).y += ((*cursor).y == 350) ? 200 : -100;
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyReturn)
        return (0);
    }
  return (1);
}

t_choice	menu(t_video *video)
{
  t_choice	choice;
  sfVector2f	cursor;
  sfVector2f	background_pos;

  cursor.x = 380;
  cursor.y = 350;
  background_pos.x = 0;
  background_pos.y = 0;
  if (!(video->background = load_texture("textures/bg.jpg")))
    exit(84);
  choice.raw_map = DEFAULT_MAP;
  video->event.key.code = 0;
  while (get_entry(video, background_pos, &cursor))
    usleep(10000);
  choice.choice = (int)trunc(cursor.y);
  if (choice.choice == 550)
    return (choice);
  cursor.y = 200;
  while (!(choice.raw_map = get_map(video, &cursor, choice.choice)))
    usleep(10000);
  choice.raw_map = my_strcat("maps/", choice.raw_map);
  return (choice);
}
