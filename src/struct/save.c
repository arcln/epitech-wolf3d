/*
** save.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/struct/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan 10 12:57:22 2017 Arthur Chaloin
** Last update Sun Jan 15 21:06:43 2017 Arthur Chaloin
*/
#include "wolf3d.h"

int	save(t_map *map)
{
  int	index;
  int	index2;
  int	fd;
  char	actual;

  index = 0;
  if ((fd = open(my_strcat("maps/", map->name), O_RDWR | O_CREAT | O_TRUNC,
		 00644)) == -1)
    exit(84);
  while (index < map->size.y)
    {
      index2 = 0;
      while (index2 < map->size.x)
	{
	  actual = map->map[index][index2] + 48;
          if (write(fd, &actual, 1) == -1)
	    exit(84);
	  index2++;
	}
      if (write(fd, "\n", 1) == -1)
	exit(84);
      index++;
    }
  close(fd);
  return (1);
}
