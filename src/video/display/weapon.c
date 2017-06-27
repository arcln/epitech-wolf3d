/*
** weapon.c for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/bonus/src/video/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Jan 10 13:08:16 2017 Arthur Chaloin
** Last update Tue Jan 10 13:13:02 2017 Arthur Chaloin
*/
#include "wolf3d.h"

static sfVector2f	get_weapon_pos(t_video *video, t_player *player)
{
  sfVector2f		pos;

  pos.x = video->mode.width -
    sfImage_getSize(video->weapon[player->weapon]).x + player->firing +
    (float)((10 + video->moving) * (float)-2 * cos((float)
    video->time->total_frames / (30000. - (video->moving * 1000)))) -
    ((video->keys->x && video->moving) ? 200 : 0);
  pos.y = (int)((float)video->mode.height -
    (float)sfImage_getSize(video->weapon[player->weapon]).y -
    (float)player->firing + 42. + (float)((10. + video->moving) * (float)
    sin((float)video->time->total_frames / (30000. - (video->moving *
    1000)) * 2))) - ((video->keys->x && video->moving) ? -250 : 0);
  return (pos);
}

void		draw_weapon(t_video *video, t_player *player)
{
  sfVector2f	pos;

  if (player->firing && video->viser == 1)
    {
      pos.x = video->mode.width -
	sfImage_getSize(video->weapon[player->weapon]).x;
      pos.y = video->mode.height -
	sfImage_getSize(video->weapon[player->weapon]).y + 60;
      draw_image(video->weapon[0], pos, video, 0);
    }
  if (video->viser != 1)
    draw_image(video->weapon[1], create_vector(-150 + (float)(12. * (float)-2 *
    cos((float)video->time->total_frames / 30000.)), -84 + (float)(12. *
    (float)sin((float)video->time->total_frames / 30000. * 2))), video, 0);
  else
    draw_image(video->weapon[player->weapon], get_weapon_pos(video, player),
	       video, (video->keys->x && video->moving) ? -30 : 0);
}
