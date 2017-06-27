/*
** keys.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Dec 28 14:21:11 2016 Arthur Chaloin
** Last update Sun Jan 15 18:43:35 2017 Arthur Chaloin
*/
#include "wolf3d.h"

t_keys		*init_keys()
{
  t_keys	*keys;

  if (!(keys = malloc(sizeof(t_keys))))
    return (NULL);
  keys->up = 0;
  keys->down = 0;
  keys->left = 0;
  keys->right = 0;
  keys->left_mouse = 0;
  keys->right_mouse = 0;
  keys->f = 0;
  keys->x = 0;
  keys->r = 0;
  return (keys);
}

void	set_keys_release(t_video *video, t_keys *keys)
{
  if (video->event.key.code == sfKeyZ)
    keys->up = 0;
  if (video->event.key.code == sfKeyS)
    keys->down = 0;
  if (video->event.key.code == sfKeyQ)
    keys->left = 0;
  if (video->event.key.code == sfKeyD)
    keys->right = 0;
  if (video->event.key.code == sfKeyF)
    keys->f = 0;
  if (video->event.key.code == sfKeyX)
    keys->x = 0;
  if (video->event.key.code == sfKeyR)
    keys->r = 0;
  if (video->event.mouseButton.button == sfMouseLeft)
    keys->left_mouse = 0;
  if (video->event.mouseButton.button == sfMouseRight)
    keys->right_mouse = 0;
}

void	set_keys_press(t_video *video, t_keys *keys)
{
  if (video->event.key.code == sfKeyZ)
    keys->up = 1;
  if (video->event.key.code == sfKeyS)
    keys->down = 1;
  if (video->event.key.code == sfKeyQ)
    keys->left = 1;
  if (video->event.key.code == sfKeyD)
    keys->right = 1;
  if (video->event.key.code == sfKeyF)
    keys->f = 1;
  if (video->event.key.code == sfKeyX)
    keys->x = 1;
  if (video->event.key.code == sfKeyR)
    keys->r = 1;
  if (video->event.mouseButton.button == sfMouseLeft)
    keys->left_mouse = 1;
  if (video->event.mouseButton.button == sfMouseRight)
    keys->right_mouse = 1;
}
