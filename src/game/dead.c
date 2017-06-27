/*
** dead.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/game/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sun Jan 15 14:06:25 2017 Arthur Chaloin
** Last update Sun Jan 15 21:13:46 2017 Arthur Chaloin
*/
#include "wolf3d.h"

void		init_pnj(t_video *video, t_map *map)
{
  int		index;
  t_entity	*new;
  t_entity	*prev;

  video->entities = NULL;
  index = 0;
  prev = NULL;
  while (index < MOB_NB)
    {
      new = create_pnj(map, video);
      if (!video->entities)
	video->entities = new;
      else
        prev->next = new;
      prev = new;
      index++;
    }
}

void		check_hit(t_video *video, t_map *map)
{
  float		dist;
  float		dir;
  float		shot;
  t_entity	*actual;

  actual = video->entities;
  while (actual)
    {
      dist = sqrt(pow(actual->pos.x - video->player.pos.x, 2) +
                  pow(actual->pos.y - video->player.pos.y, 2));
      dir = get_direction(video->player.pos, actual->pos, dist);
      shot = fabsf(video->player.dir - dir);
      if ((shot < 8. || shot > 257.) && is_visible(dist, dir, map, video))
	{
	  actual->pos = generate_pos(map, video);
	  video->kill = 0;
	  video->headshot = (video->y_axis > 20);
	  video->score += (video->headshot) ? 100 : 50;
	}
      actual = actual->next;
    }
}

static void	draw_dead_screen(t_video *video)
{
  sfImage	*bg;

  bg = load_texture("textures/map/dead.jpg");
  clear(video);
  sfRenderWindow_clear(video->window, sfWhite);
  draw_image(bg, create_vector(-290, 0), video, 0);
  draw_white_text(my_strcat("Score : ", my_strnbr(video->score)), 84,
            create_vector(600, 590), video, "fonts/BGB.ttf");
  sfRenderWindow_display(video->window);
}

void		dead(t_video *video, t_map *map)
{
  sfMusic_stop(video->music);
  draw_dead_screen(video);
  while (1)
    {
      while (sfRenderWindow_pollEvent(video->window, &(video->event)))
	{
	  if (video->event.type == sfEvtClosed ||
	      (video->event.type == sfEvtKeyPressed &&
	       video->event.key.code == sfKeyEscape))
	    exit(0);
	  if (video->event.type == sfEvtKeyPressed &&
	      video->event.key.code == sfKeyReturn)
	    {
	      init_pnj(video, map);
	      video->keys = init_keys();
	      video->kill = -1;
	      video->score = 0;
	      video->player.pos = get_start(map);
	      sfMusic_play(video->music);
	      return;
	    }
	}
    }
}
