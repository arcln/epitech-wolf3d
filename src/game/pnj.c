/*
** pnj.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sat Jan 14 16:59:53 2017 Arthur Chaloin
** Last update Sun Jan 15 17:23:27 2017 Arthur Chaloin
*/
#include "wolf3d.h"

float		get_direction(sfVector2f posA, sfVector2f posB, float distance)
{
  float		adj;
  float		direction;

  adj = fabsf(posB.x - posA.x);
  direction = acos(adj / distance);
  direction = direction * 180. / M_PI;
  if (posB.x <= posA.x && posB.y > posA.y)
    direction = 180. - direction;
  else if (posB.x <= posA.x && posB.y <= posA.y)
    direction = 180. + direction;
  else if (posB.x > posA.x && posB.y <= posA.y)
    direction = 360. - direction;
  return (direction);
}

void		draw_players(t_video *video, t_map *map, t_player *player)
{
  float		distance;
  float		direction;
  t_entity	*actual;

  actual = video->entities;
  while (actual)
    {
      distance = sqrt(pow(actual->pos.x - player->pos.x, 2) +
		      pow(actual->pos.y - player->pos.y, 2));
      direction = get_direction(player->pos, actual->pos, distance);
      draw_player(map, distance, direction, video);
      actual = actual->next;
    }
}

static void	move(t_entity *actual, t_map *map, t_video *video)
{
  float		distance;
  float		direction;

  distance = sqrt(pow(actual->pos.x - video->player.pos.x, 2) +
                  pow(actual->pos.y - video->player.pos.y, 2));
  direction = get_direction(actual->pos, video->player.pos, distance);
  actual->pos = pnj_move_forward(actual->pos, direction, MOB_SPD, map);
}

static int	check_death(sfVector2f posA, sfVector2f posB)
{
  if (posA.x - posB.x > -0.5 &&
      posA.x - posB.x < 0.5 &&
      posA.y - posB.y > -0.5 &&
      posA.y - posB.y < 0.5)
    return (1);
  return (0);
}

int	handle_pnj(t_video *video, t_map *map)
{
  t_entity	*actual;

  actual = video->entities;
  while (actual)
    {
      move(actual, map, video);
      if (check_death(actual->pos, video->player.pos))
	return (1);
      actual = actual->next;
    }
  return (0);
}
