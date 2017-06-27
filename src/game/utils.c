/*
** utils.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Dec 27 15:54:25 2016 Arthur Chaloin
** Last update Tue Dec 27 16:10:01 2016 Arthur Chaloin
*/
#include "wolf3d.h"

sfColor		create_color(int r, int g, int b)
{
  sfColor	color;

  color.r = r;
  color.g = g;
  color.b = b;
  color.a = 255;
  return (color);
}

sfVector2f	create_vector(float x, float y)
{
  sfVector2f	ret;

  ret.x = x;
  ret.y = y;
  return (ret);
}
