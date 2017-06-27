/*
** blit.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/video/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Thu Jan  5 23:18:52 2017 Arthur Chaloin
** Last update Sun Jan 15 17:39:51 2017 Arthur Chaloin
*/
#include "wolf3d.h"

void		draw_image(sfImage *image, sfVector2f pos,
			   t_video *video, float angle)
{
  sfSprite	*sprite;
  sfTexture	*texture;

  sprite = sfSprite_create();
  texture = sfTexture_createFromImage(image, NULL);
  sfSprite_setTexture(sprite, texture, 1);
  sfSprite_setPosition(sprite, pos);
  sfSprite_setRotation(sprite, angle);
  sfRenderWindow_drawSprite(video->window, sprite, NULL);
  sfTexture_destroy(texture);
  sfSprite_destroy(sprite);
}

void		draw_white_text(char *raw_text, int size,
			        sfVector2f pos, t_video *video,
			        char *raw_font)
{
  sfText	*text;
  sfFont	*font;

  if (!raw_text[0])
    return;
  font = sfFont_createFromFile(raw_font);
  text = sfText_create();
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, size);
  sfText_setColor(text, sfWhite);
  sfText_setString(text, raw_text);
  sfText_setPosition(text, pos);
  sfRenderWindow_drawText(video->window, text, NULL);
  sfText_destroy(text);
  sfFont_destroy(font);
}

void		draw_text(char *raw_text, int size,
			  sfVector2f pos, t_video *video,
			  char *raw_font)
{
  sfText	*text;
  sfFont	*font;

  if (!raw_text[0])
    return;
  font = sfFont_createFromFile(raw_font);
  text = sfText_create();
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, size);
  sfText_setColor(text, sfBlack);
  sfText_setString(text, raw_text);
  sfText_setPosition(text, pos);
  sfRenderWindow_drawText(video->window, text, NULL);
  sfText_destroy(text);
  sfFont_destroy(font);
}

static sfColor	get_color(t_wall *wall, t_video *video,
			  double img_x, double img_y)
{
  sfColor	color;

  color = sfImage_getPixel(video->textures[wall->texture],
			   img_x, round(img_y));
  if (wall->side)
    {
      color.r *= 0.7;
      color.g *= 0.7;
      color.b *= 0.7;
    }
  return (color);
}

void		draw_texture(t_video *video,
		             sfVector2i from,
			     sfVector2i to,
			     t_wall *wall)
{
  double	img_y;
  double	img_x;
  sfVector2u	size;
  sfVector2i	origin;

  origin = from;
  size = sfImage_getSize(video->textures[wall->texture]);
  img_x = wall->hit_pos * size.x;
  img_y = 0;
  if (from.y < 0)
    {
      from.y = 0;
      img_y += (float)size.y / fabsf(to.y - origin.y) * -origin.y;
    }
  while (from.y != to.y && (unsigned int)from.y <= video->mode.height)
    {
      put_pixel(video->fb, from.x, from.y,
		get_color(wall, video, img_x, img_y));
      from.y++;
      img_y += (float)size.y / fabsf(to.y - origin.y);
    }
}
