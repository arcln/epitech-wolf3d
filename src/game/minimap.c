/*
** minimap.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Thu Jan  5 22:44:41 2017 Arthur Chaloin
** Last update Sun Jan 15 18:50:51 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	display_fov(t_video *video, t_player *player, t_map *map)
{
  float		scan;
  float		actual_angle;
  t_wall	wall;
  sfVector2f	tmp;
  sfVector2i	end;
  sfVector2i	pos;

  scan = 0;
  actual_angle = player->dir - (video->fov / 2.);
  pos.x = (int)round(player->pos.x * MINIMAP_SIZE);
  pos.y = (int)round(player->pos.y * MINIMAP_SIZE) + video->mode.height -
      (MINIMAP_SIZE * map->size.y);
  while ((unsigned int)trunc(scan) < video->mode.width)
    {
      wall = raycast(player->pos, actual_angle, map->map, map->size);
      tmp = move_forward(player->pos, actual_angle, wall.distance);
      end.x = (int)round(tmp.x * MINIMAP_SIZE);
      end.y = (int)round(tmp.y * MINIMAP_SIZE) + video->mode.height -
	  (MINIMAP_SIZE * map->size.y);
      draw_true_line(video->fb, pos, end, sfBlue);
      actual_angle = actual_angle + ((video->fov / video->viser /
				      (float)video->mode.width));
      scan += 1;
    }
}

static void	draw_case(int index, int index2, t_video *video, t_map *map)
{
  sfVector2i	pos;

  if (map->map[index][index2] <= 1)
    {
      pos.x = MINIMAP_SIZE * index2;
      pos.y = MINIMAP_SIZE * index + video->mode.height -
          (MINIMAP_SIZE * map->size.y);
      draw_square(video->fb, pos, MINIMAP_SIZE, sfWhite);
    }
  else
    {
      pos.x = MINIMAP_SIZE * index2;
      pos.y = MINIMAP_SIZE * index + video->mode.height -
          (MINIMAP_SIZE * map->size.y);
      draw_square(video->fb, pos, MINIMAP_SIZE,
                  create_color(map->map[index][index2] * 25,
                               map->map[index][index2] * 25,
                               map->map[index][index2] * 25));
    }
}

static void	display_pnj(t_video *video, t_map *map)
{
  t_entity	*actual;
  sfVector2i	pos;

  actual = video->entities;
  while (actual)
    {
      pos.x = (int)round(actual->pos.x * MINIMAP_SIZE) - (MINIMAP_SIZE / 2);
      pos.y = (int)round(actual->pos.y * MINIMAP_SIZE) + video->mode.height -
	(MINIMAP_SIZE * map->size.y) - (MINIMAP_SIZE / 2);
      if (video->radar)
        draw_square(video->fb, pos, MINIMAP_SIZE, sfRed);
      actual = actual->next;
    }
}

void		draw_minimap(t_video *video, t_map *map, t_player *player)
{
  int		index;
  int		index2;
  sfVector2i	pos;

  index = 0;
  index2 = 0;
  while (index < map->size.y)
    {
      while (index2 < map->size.x)
	{
	  draw_case(index, index2, video, map);
	  index2++;
	}
      index2 = 0;
      index++;
    }
  display_fov(video, player, map);
  display_pnj(video, map);
  pos.x = (int)round(player->pos.x * MINIMAP_SIZE) - (MINIMAP_SIZE / 2);
  pos.y = (int)round(player->pos.y * MINIMAP_SIZE) + video->mode.height -
      (MINIMAP_SIZE * map->size.y) - (MINIMAP_SIZE / 2);
  draw_square(video->fb, pos, MINIMAP_SIZE, sfGreen);
}
