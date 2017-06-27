/*
** video.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 09:26:23 2016 Arthur Chaloin
** Last update Sun Jan 15 19:04:08 2017 Arthur Chaloin
*/
#include "wolf3d.h"

sfImage			*load_texture(char *path)
{
  sfImage		*img;

  img = sfImage_createFromFile(path);
  if (!img)
    exit(84);
  return (img);
}

static void		init_textures(t_video *video)
{
  int			index;
  int			index2;
  char			**text;

  index = -1;
  index2 = 0;
  text = map_file(TEXTURE_FILE_PATH);
  if (!(video->textures = malloc(sizeof(sfImage *) * (my_tablen(text + 1)))) ||
      !(video->weapon = malloc(sizeof(sfImage *) * my_tablen(text) + 1)) ||
      !(video->weapon_speed = malloc(sizeof(int) * my_tablen(text) + 1)))
    exit(84);
  while (text[++index] && text[index][0] != '\0')
    video->textures[index] = load_texture(text[index]);
  video->textures[index] = NULL;
  index++;
  while (text[index - 1] && text[index])
    {
      video->weapon[index2] = load_texture(text[index]);
      video->weapon_speed[index2] = my_getnbr(text[index + 1]);
      index += 2;
      index2++;
    }
  video->sky = load_texture("textures/map/sky.jpg");
  video->skypos.x = 0;
  video->skypos.y = -420;
}

static t_my_framebuffer	*my_framebuffer_create(int width, int height)
{
  int			cursor;
  t_my_framebuffer	*buffer;

  if (!(buffer = malloc(sizeof(t_my_framebuffer))) ||
      !(buffer->pixels = malloc(sizeof(sfUint8) * (width * height * 4))))
    return (NULL);
  buffer->width = width;
  buffer->height = height;
  cursor = 0;
  while (cursor < width * height * 4)
    {
      buffer->pixels[cursor] = 0;
      cursor++;
    }
  return (buffer);
}

static void	init_video_data(t_video *video)
{
  video->mode.width = WIDTH;
  video->mode.height = HEIGHT;
  video->mode.bitsPerPixel = 32;
  video->window = sfRenderWindow_create(video->mode, "wolf3d", V_MODE, NULL);
  video->fb = my_framebuffer_create(video->mode.width, video->mode.height);
  video->texture = sfTexture_create(WIDTH, HEIGHT);
  video->sprite = sfSprite_create();
  video->fps = NULL;
  video->center.x = WIDTH / 2;
  video->center.y = HEIGHT / 2;
  video->y_axis = 0;
  video->viser = 0;
  video->moving = 0;
  video->fov = 90;
  video->fps = sfText_create();
  video->shot = sfMusic_createFromFile("sound/shot.wav");
  video->uav = sfMusic_createFromFile("sound/uav.wav");
  video->music = sfMusic_createFromFile("sound/ost.wav");
  video->keys = init_keys();
  video->kill = -1;
  video->headshot = 0;
  video->score = 0;
  video->radar = 0;
  video->player_sprite[0] = load_texture("textures/map/mob.png");
}

t_video		*init_video()
{
  t_video	*video;
  sfFont	*font;

  if (!(video = malloc(sizeof(t_video))))
    return (NULL);
  init_video_data(video);
  font = sfFont_createFromFile("fonts/BGB.ttf");
  sfText_setFont(video->fps, font);
  sfText_setCharacterSize(video->fps, 24);
  sfText_setColor(video->fps, sfBlack);
  sfRenderWindow_setFramerateLimit(video->window, 144);
  sfSprite_setTexture(video->sprite, video->texture, sfTrue);
  init_textures(video);
  return (video);
}
