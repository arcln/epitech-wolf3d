/*
** events.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 18:16:50 2016 Arthur Chaloin
** Last update Sun Jan 15 18:52:29 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	handle_camera(t_player *player, t_video *video, t_keys *keys)
{
  static int	mouse_x = 0;
  static int	mouse_y = 0;

  video->fov = (keys->f) ? 359 : 90;
  if (video->event.type == sfEvtMouseMoved &&
      video->event.mouseMove.x < mouse_x)
    {
      player->dir -= R_SPD * (mouse_x - video->event.mouseMove.x);
      video->skypos.x += 16 * R_SPD * (mouse_x - video->event.mouseMove.x);
    }
  if (video->event.type == sfEvtMouseMoved &&
      video->event.mouseMove.x > mouse_x)
    {
      player->dir += R_SPD * (video->event.mouseMove.x - mouse_x);
      video->skypos.x -= 16 * R_SPD * (video->event.mouseMove.x - mouse_x);
    }
  if (video->event.type == sfEvtMouseMoved &&
      video->event.mouseMove.y < mouse_y && video->y_axis < 100)
    video->y_axis -= 4 * R_SPD * (video->event.mouseMove.y - mouse_y);
  if (video->event.type == sfEvtMouseMoved &&
      video->event.mouseMove.y > mouse_y && video->y_axis > -100)
    video->y_axis -= 4 * R_SPD * (video->event.mouseMove.y - mouse_y);
  sfMouse_setPosition(video->center, (const sfWindow *)video->window);
  mouse_x = video->center.x;
  mouse_y = video->center.y;
}

static void	handle_weapon(t_keys *keys, t_player *player,
			      t_video *video, t_map *map)
{
  static int	fire = 0;

  if (keys->left_mouse)
    {
      if (fire % video->weapon_speed[player->weapon] == 0)
	{
	  sfMusic_stop(video->shot);
          player->firing = 42;
	  check_hit(video, map);
	  sfMusic_play(video->shot);
	}
      else
	player->firing = 0;
      fire++;
    }
  else
    {
      player->firing = 0;
      fire = 0;
    }
  if (keys->right_mouse)
    video->viser = 4;
  else
    video->viser = 1;
}

void	action(t_player *player, t_keys *keys,
			    t_map *map, t_video *video)
{
  if (keys->up || keys->down || keys->right || keys->left)
    video->moving = (keys->x) ? 20 : 10;
  else
    video->moving = 0;
  if (keys->up)
    player->pos = t_move_forward(player->pos, player->dir, (keys->x) ?
				 P_SPD * 2 : P_SPD, map);
  if (keys->down)
    player->pos = t_move_forward(player->pos, player->dir, (keys->x) ?
				 -P_SPD * 2 : -P_SPD, map);
  if (keys->left)
    player->pos = t_move_forward(player->pos, player->dir + 90, -P_SPD, map);
  if (keys->right)
    player->pos = t_move_forward(player->pos, player->dir + 90, P_SPD, map);
  if (keys->r)
	{
	  sfMusic_stop(video->uav);
	  video->radar = 1;
	  if (video->radar)
            sfMusic_play(video->uav);
	}
  handle_weapon(keys, player, video, map);
  handle_camera(player, video, keys);
}

int	handle_events(t_video *video, t_keys *keys)
{
  while (sfRenderWindow_pollEvent(video->window, &(video->event)))
    {
      if (video->event.type == sfEvtClosed ||
          (video->event.type == sfEvtKeyPressed &&
           video->event.key.code == sfKeyEscape))
	return (0);
      if (video->event.type == sfEvtKeyPressed ||
          video->event.type == sfEvtMouseButtonPressed)
        set_keys_press(video, keys);
      if (video->event.type == sfEvtKeyReleased ||
          video->event.type == sfEvtMouseButtonReleased)
        set_keys_release(video, keys);
    }
  return (1);
}
