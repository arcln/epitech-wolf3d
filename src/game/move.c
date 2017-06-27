/*
** move_forward.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 09:38:20 2016 Arthur Chaloin
** Last update Sun Jan 15 16:53:22 2017 Arthur Chaloin
*/
#include "wolf3d.h"

sfVector2f	pnj_move_forward(sfVector2f pos, float direction,
			       float distance, t_map *map)
{
  sfVector2f	tmp;
  sfVector2f	tmp2;
  sfVector2f	tmp3;
  sfVector2f	final;

  tmp.x = pos.x + (distance * cos(direction * M_PI / 180.));
  tmp.y = pos.y + (distance * sin(direction * M_PI / 180.));
  tmp2.x = pos.x + (distance * 2 * cos(direction * M_PI / 180.));
  tmp2.y = pos.y + (distance * 2 * sin(direction * M_PI / 180.));
  tmp3 = move_forward(tmp2, direction - 90, 1);
  if ((int)trunc(tmp2.x) > 0 && (int)trunc(tmp2.x) < map->size.x &&
      map->map[(int)trunc(pos.y)][(int)trunc(tmp2.x)] <= 1 &&
      (int)trunc(tmp3.x) > 0 && (int)trunc(tmp3.x) < map->size.x &&
          map->map[(int)trunc(pos.y)][(int)trunc(tmp3.x)] <= 1)
    final.x = tmp.x;
  else
    final.x = pos.x;
  if ((int)trunc(tmp2.y) > 0 && (int)trunc(tmp2.y) < map->size.y &&
      map->map[(int)trunc(tmp2.y)][(int)trunc(pos.x)] <= 1 &&
      (int)trunc(tmp3.y) > 0 && (int)trunc(tmp3.y) < map->size.y &&
          map->map[(int)trunc(tmp3.y)][(int)trunc(pos.x)] <= 1)
    final.y = tmp.y;
  else
    final.y = pos.y;
  return (final);
}

sfVector2f	t_move_forward(sfVector2f pos, float direction,
			       float distance, t_map *map)
{
  sfVector2f	tmp;
  sfVector2f	tmp2;
  sfVector2f	final;

  tmp.x = pos.x + (distance * cos(direction * M_PI / 180.));
  tmp.y = pos.y + (distance * sin(direction * M_PI / 180.));
  tmp2.x = pos.x + (distance * 2 * cos(direction * M_PI / 180.));
  tmp2.y = pos.y + (distance * 2 * sin(direction * M_PI / 180.));
  if ((int)trunc(tmp2.x) > 0 && (int)trunc(tmp2.x) < map->size.x &&
      map->map[(int)trunc(pos.y)][(int)trunc(tmp2.x)] <= 1)
    final.x = tmp.x;
  else
    final.x = pos.x;
  if ((int)trunc(tmp2.y) > 0 && (int)trunc(tmp2.y) < map->size.y &&
      map->map[(int)trunc(tmp2.y)][(int)trunc(pos.x)] <= 1)
    final.y = tmp.y;
  else
    final.y = pos.y;
  return (final);
}

sfVector2f	move_forward(sfVector2f pos, float direction, float distance)
{
  sfVector2f	final;

  final.x = pos.x + (distance * cos(direction * M_PI / 180.));
  final.y = pos.y + (distance * sin(direction * M_PI / 180.));
  return (final);
}
