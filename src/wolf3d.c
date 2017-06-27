/*
** wolf3d.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 09:20:05 2016 Arthur Chaloin
** Last update Sun Jan 15 15:12:51 2017 Arthur Chaloin
*/
#include "wolf3d.h"

int		wolf3d()
{
  int		game;
  t_choice	choice;
  t_video	*video;
  t_map		*map;

  game = 1;
  video = init_video();
  while (game)
    {
      choice = menu(video);
      if (choice.choice == 350)
	{
          map = load_map(choice.raw_map);
	  game_loop(video, map, video->keys);
	}
      else if (choice.choice == 450)
	editor(video, choice.raw_map, video->keys);
      else
	exit(0);
    }
  return (0);
}

int		main()
{
  wolf3d();
  return (0);
}
