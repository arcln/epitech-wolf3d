/*
** load_map.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 10:39:56 2016 Arthur Chaloin
** Last update Sun Jan 15 21:26:34 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	convert_int(t_map *map, char **tab)
{
  int		index;
  int		index2;
  int		str_cursor;

  index = 0;
  str_cursor = 0;
  if (!(map->map = malloc(sizeof(int *) * (map->size.y + 1)))) exit(84);
  while (index < map->size.y)
    {
      index2 = 0;
      if (!(map->map[index] = malloc(sizeof(int) * (map->size.x + 1))))
	return;
      if ((tab[index][index2] > '5' || tab[index][index2] < '0') &&
	  tab[index][index2] != ' ')
	exit(84);
      while (index2 < map->size.x)
	{
	  map->map[index][index2] = (tab[index][index2] == ' ') ?
	      0 : tab[index][str_cursor] - 48;
	  str_cursor++;
	  index2++;
	}
      str_cursor = 0;
      index++;
    }
}

t_map	*load_map(char *path)
{
  t_map	*map;
  char	**tab;

  if (!(tab = map_file(path)))
    return (NULL);
  if (!(map = malloc(sizeof(t_map))))
    return (NULL);
  map->size.x = my_strlen(tab[0]);
  map->size.y = my_tablen(tab);
  map->name = path + 5;
  if (!map->size.x || !map->size.y)
    exit(84);
  convert_int(map, tab);
  return (map);
}
