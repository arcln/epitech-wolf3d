/*
** wolf3d.h for wolf3d in /home/arthur/Documents/B1-C_Graph_Prog/wolf3d/include/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Dec 12 09:22:38 2016 Arthur Chaloin
** Last update Sat Mar 18 15:48:18 2017 Arthur Chaloin
*/

#ifndef WOLF_3D_H_
# define WOLF_3D_H_

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <SFML/Graphics.h>
# include <SFML/System.h>
# include <SFML/Window.h>
# include <SFML/Audio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include "my.h"

# define WIDTH		1280
# define HEIGHT		720
# define V_MODE		sfResize | sfClose

# define FRAMETIME		16666
# define ZOOM			2.0
# define DEFAULT_DIR		0.
# define R_SPD			0.15
# define P_SPD			0.10
# define MOB_SPD		0.10
# define MOB_NB			5
# define MINIMAP_SIZE		6
# define VALUE			0

# define DEFAULT_MAP		"maps/default"
# define TEXTURE_FILE_PATH	"textures/texture.ws"
# define FONT			"fonts/default.ttf"
# define FONT2			"fonts/direwolf3d.ttf"

# define MIN(x, y)	(x < y) ? x : y

typedef struct		s_my_framebuffer
{
  sfUint8		*pixels;
  int			width;
  int			height;
}			t_my_framebuffer;

typedef struct		s_player_data
{
  sfVector2f		pos;
  float			dir;
  int			weapon;
  int			firing;
}			t_player;

typedef struct		s_time_data
{
  int			frame_nb;
  unsigned long long	total_frames;
  int			elapsed;
  sfTime		sleep;
  sfClock		*frame;
}			t_time;

typedef struct		s_key_data
{
  int			down;
  int			up;
  int			left;
  int			right;
  int			left_mouse;
  int			right_mouse;
  int			f;
  int			x;
  int			r;
}			t_keys;

typedef struct		s_entity
{
  sfVector2f		pos;
  int			dir;
  struct s_entity	*next;
}			t_entity;

typedef struct		s_video_data
{
  t_my_framebuffer	*fb;
  sfRenderWindow	*window;
  sfVideoMode		mode;
  sfVector2f		skypos;
  sfVector2i		center;
  sfTexture		*texture;
  sfSprite		*sprite;
  sfEvent		event;
  sfImage		**textures;
  sfImage		*sky;
  sfImage		**weapon;
  sfImage		*background;
  sfImage		*player_sprite[4];
  sfMusic		*shot;
  sfMusic		*uav;
  sfMusic		*music;
  sfText		*fps;
  t_player		player;
  t_entity		*entities;
  t_time		*time;
  t_keys		*keys;
  float			fov;
  int			*weapon_speed;
  int			y_axis;
  int			viser;
  int			moving;
  int			kill;
  int			headshot;
  int			score;
  int			radar;
}			t_video;

typedef struct		s_map_data
{
  int			**map;
  char			*name;
  sfVector2i		size;
}			t_map;

typedef struct		s_wall_data
{
  double		hit_pos;
  float			distance;
  int			side;
  int			texture;
}			t_wall;

typedef struct		s_ray_data
{
  float			distance;
  sfVector2i		pos;
  sfVector2f		fpos;
}			t_ray;

typedef struct		s_file
{
  char			*name;
  char			type;
  struct stat		info;
}			t_file;

typedef struct		s_list
{
  t_file		*file;
  struct s_list		*next;
  struct s_list		*prev;
}			t_list;

typedef struct		s_choice
{
  int			choice;
  char			*raw_map;
}			t_choice;

void		init_calcs();
t_video		*init_video();
t_keys		*init_keys();
t_map		*load_map(char *path);
void		game_loop(t_video *video, t_map *map, t_keys *keys);
sfVector2f	move_forward(sfVector2f pos, float direction, float distance);
sfVector2f	t_move_forward(sfVector2f pos, float direction,
				  float distance, t_map *map);
void		display(t_player *player, t_map *map, t_video *video);
void		update_fps(t_time *time, t_video *video);
void		draw_minimap(t_video *video, t_map *map, t_player *player);
int		handle_events(t_video *video, t_keys *keys);
void		action(t_player *player, t_keys *keys,
			    t_map *map, t_video *video);
void		set_keys_press(t_video *video, t_keys *keys);
void		set_keys_release(t_video *video, t_keys *keys);
void		clear(t_video *video);
t_wall		raycast(sfVector2f pos, float dir,
			int **map, sfVector2i map_size);
void		put_pixel(t_my_framebuffer *framebuff,
			     int x,
			     int y,
			     sfColor color);
void		draw_line(t_my_framebuffer *framebuff,
			     sfVector2i from_int,
			     sfVector2i to,
			     sfColor color);
void		draw_true_line(t_my_framebuffer *framebuff,
			       sfVector2i from_int,
			       sfVector2i to,
			       sfColor color);
void		draw_square(t_my_framebuffer *fb, sfVector2i pos,
			    int size, sfColor color);
void		draw_texture(t_video *video,
			     sfVector2i from,
			     sfVector2i to,
			     t_wall *wall);
void		draw_text(char *text, int size,
			  sfVector2f pos, t_video *video,
			  char *font);
void		draw_white_text(char *raw_text, int size,
			        sfVector2f pos, t_video *video,
			        char *raw_font);
void		draw_image(sfImage *image, sfVector2f pos,
			   t_video *video, float angle);
sfColor		create_color(int r, int g, int b);
sfVector2f	create_vector(float x, float y);
void		wait_key(t_video *video);
t_list		*collect_data(DIR *dir, char *path);
t_choice	menu(t_video *video);
void		editor(t_video *video, char *raw_map, t_keys *keys);
t_map		*new_map(t_video *video);
void		display_map(t_map *map, t_video *video);
void		display_textures(t_video *video, int actual);
int		save(t_map *map);
void		draw(t_wall *wall, unsigned int scan, t_video *video, float a);
void		draw_weapon(t_video *video, t_player *player);
void		draw_sky(t_video *video);
char		*get_map(t_video *video, sfVector2f *actual, int choice);
void		draw_players(t_video *video, t_map *map, t_player *player);
int		handle_pnj(t_video *video, t_map *map);
void		draw_player(t_map *map, float dist, float dir, t_video *video);
void		dead(t_video *video, t_map *map);
sfVector2f	get_start(t_map *map);
t_entity	*create_pnj(t_map *map, t_video *video);
void		init_pnj(t_video *video, t_map *map);
sfVector2f	pnj_move_forward(sfVector2f pos, float direction,
			       float distance, t_map *map);
float		get_direction(sfVector2f posA, sfVector2f posB,
			      float distance);
void		check_hit(t_video *video, t_map *map);
sfVector2f	generate_pos(t_map *map, t_video *video);
int		is_visible(float distance, float direction,
			   t_map *map, t_video *video);
sfImage		*load_texture(char *path);

#endif /* !WOLF_3D_H_ */
