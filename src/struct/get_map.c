/*
** get_map.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/struct/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan 10 13:17:53 2017 Arthur Chaloin
** Last update Sun Jan 15 21:07:38 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static int	list_maps(t_video *video, sfVector2f actual)
{
  int		count;
  DIR		*dir;
  t_list	*files_list;

  count = 0;
  if (!(dir = opendir("./maps")))
    exit(84);
  if (!(files_list = collect_data(dir, "./maps/")))
    exit(84);
  while (files_list)
    {
      if (files_list->file->name[0] != '.')
	{
          draw_white_text(files_list->file->name, 42,
		    create_vector(420, count * 60 + 200),
		    video, "fonts/default.ttf");
          count++;
	}
      files_list = files_list->next;
    }
  draw_white_text(">", 42, actual, video, "fonts/default.ttf");
  return (count);
}

static char	*get_name(sfVector2f actual)
{
  int		count;
  DIR		*dir;
  t_list	*files_list;

  count = 0;
  if (!(dir = opendir("./maps")))
    exit(84);
  if (!(files_list = collect_data(dir, "./maps/")))
    exit(84);
  while ((200 + (60 * (count)) != actual.y && files_list) ||
	 files_list->file->name[0] == '.')
    {
      if (files_list->file->name[0] != '.')
	count++;
      files_list = files_list->next;
    }
  closedir(dir);
  if (!(files_list))
    exit(84);
  return (files_list->file->name);
}

static char	*get_events(t_video *video, sfVector2f *actual,
			    int *count, int *choice)
{
  while (sfRenderWindow_pollEvent(video->window, &(video->event)))
    {
      if (video->event.type == sfEvtClosed)
        exit(0);
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyDown)
        (*actual).y += ((*actual).y == 200 + 60 * (*count - 1)) ?
	  -60 * (*count - 1) : 60;
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyUp)
        (*actual).y += ((*actual).y == 200) ? 60 * (*count - 1) : -60;
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyReturn)
        return (get_name(*actual));
      if (video->event.type == sfEvtKeyPressed &&
          video->event.key.code == sfKeyTab && *choice == 450)
        return ("_NEWMAP");
   }
  return (NULL);
}

char		*get_map(t_video *video, sfVector2f *actual, int choice)
{
  int		count;
  char		*result;

  clear(video);
  sfRenderWindow_clear(video->window, sfBlack);
  draw_image(video->background, create_vector(0, 0), video, 0);
  if (choice == 450)
    draw_white_text("Press  TAB  to  create  a  map", 37,
		    create_vector(700, 600), video, "fonts/default.ttf");
  count = list_maps(video, *actual);
  sfRenderWindow_display(video->window);
  if ((result = get_events(video, actual, &count, &choice)))
    return (result);
  return (NULL);
}
