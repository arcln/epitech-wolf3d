/*
** editor_display.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/editor/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan 10 12:46:44 2017 Arthur Chaloin
** Last update Sun Jan 15 19:04:00 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static void	draw_case(int texture_nb, sfVector2f pos,
			  int size, t_video *video)
{
  sfSprite	*sprite;
  sfTexture	*texture;
  sfVector2i	actual;

  if (texture_nb < 2)
    {
      actual.x = pos.x * size + 50;
      actual.y = pos.y * size + 50;
      draw_square(video->fb, actual, size, sfWhite);
      return;
    }
  sprite = sfSprite_create();
  texture = sfTexture_createFromImage(video->textures[texture_nb - 2], NULL);
  sfSprite_setTexture(sprite, texture, 1);
  sfSprite_setPosition(sprite, create_vector(pos.x * size + 50,
                                             pos.y * size + 50));
  sfSprite_setScale(sprite, create_vector((float)size /
                       sfSprite_getLocalBounds(sprite).width,
                       (float)size / sfSprite_getLocalBounds(sprite).width));
  sfRenderWindow_drawSprite(video->window, sprite, NULL);
  sfTexture_destroy(texture);
  sfSprite_destroy(sprite);
}

void	display_map(t_map *map, t_video *video)
{
  int	index;
  int	index2;
  int	size;

  index = 0;
  index2 = 0;
  size = MIN((video->mode.width - 300.) / map->size.x,
	     (video->mode.height - 100.) / map->size.y);
  while (index < map->size.y)
    {
      while (index2 < map->size.x)
	{
	  draw_case(map->map[index][index2], create_vector(index2, index),
		    size, video);
	  index2++;
	}
      index2 = 0;
      index++;
    }
}

static void	draw_cursor(int actual, t_video *video)
{
  sfSprite	*sprite;
  sfTexture	*texture;
  sfImage	*image;

  image = load_texture("textures/editor/cursor.png");
  sprite = sfSprite_create();
  texture = sfTexture_createFromImage(image, NULL);
  sfSprite_setTexture(sprite, texture, 1);
  sfSprite_setPosition(sprite,
                       create_vector(video->mode.width - 266,
                      (actual * 60) + 50 + (4 * actual)));
  sfSprite_setScale(sprite, create_vector(60. /
                    sfSprite_getLocalBounds(sprite).width,
                    60. / sfSprite_getLocalBounds(sprite).width));
  sfRenderWindow_drawSprite(video->window, sprite, NULL);
  sfTexture_destroy(texture);
  sfSprite_destroy(sprite);
}

void		display_textures(t_video *video, int actual)
{
  int		index;
  sfSprite	*sprite;
  sfTexture	*texture;

  index = 0;
  while (video->textures[index])
    {
      sprite = sfSprite_create();
      texture = sfTexture_createFromImage(video->textures[index], NULL);
      sfSprite_setTexture(sprite, texture, 1);
      sfSprite_setPosition(sprite,
			   create_vector(video->mode.width - 200,
					 index * 60 + 4 * index + 50));
      sfSprite_setScale(sprite, create_vector(60. /
                           sfSprite_getLocalBounds(sprite).width,
			   60. / sfSprite_getLocalBounds(sprite).width));
      sfRenderWindow_drawSprite(video->window, sprite, NULL);
      sfTexture_destroy(texture);
      sfSprite_destroy(sprite);
      index++;
    }
  draw_cursor(actual, video);
}
