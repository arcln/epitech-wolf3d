/*
** pnj_core.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sun Jan 15 15:01:02 2017 Arthur Chaloin
** Last update Sun Jan 15 21:23:26 2017 Arthur Chaloin
*/
#include "wolf3d.h"

sfVector2f	generate_pos(t_map *map, t_video *video)
{
  float		dist;
  float		dir;
  sfVector2f	pos;

  do
    {
      pos.x = ((double)rand() / (double)(RAND_MAX)) * (double)map->size.x;
      pos.y = ((double)rand() / (double)(RAND_MAX)) * (double)map->size.y;
      dist = sqrt(pow(pos.x - video->player.pos.x, 2) +
                  pow(pos.y - video->player.pos.y, 2));
      dir = get_direction(video->player.pos, pos, dist);
    } while (map->map[(int)trunc(pos.y)][(int)trunc(pos.x)] ||
	     is_visible(dist, dir, map, video));
  return (pos);
}

t_entity	*create_pnj(t_map *map, t_video *video)
{
  t_entity	*new;

  if (!(new = malloc(sizeof(t_entity))))
    exit(84);
  new->pos = generate_pos(map, video);
  new->dir = 0;
  new->next = NULL;
  return (new);
}
