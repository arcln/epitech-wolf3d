/*
** map_file.c for lib in /home/arthur/Documents/lib/my/src/parsing/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Dec  6 09:33:53 2016 Arthur Chaloin
** Last update Sun Jan 15 19:47:50 2017 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*get_next_line(char *path);

static int	count_lines(char *path)
{
  int		fd;
  int		lines_nb;
  char		buffer[2];

  if (!strcmp(path, "reset"))
    return (0);
  lines_nb = 0;
  buffer[1] = '\0';
  if (!(fd = open(path, O_RDONLY)))
    return (-1);
  while (read(fd, buffer, 1))
    {
      if (buffer[0] == '\n')
	lines_nb++;
    }
  close(fd);
  return (lines_nb);
}

char	**map_file(char *path)
{
  int		index;
  int		lines_nb;
  char		*buffer;
  char		**str_map;

  index = 0;
  lines_nb = count_lines(path);
  if (!lines_nb)
    exit(84);
  if (!(str_map = malloc(sizeof(char *) * (lines_nb + 1))))
    return (NULL);
  while ((buffer = get_next_line(path)))
    {
      str_map[index] = buffer;
      index++;
    }
  str_map[index] = NULL;
  free(buffer);
  return (str_map);
}
