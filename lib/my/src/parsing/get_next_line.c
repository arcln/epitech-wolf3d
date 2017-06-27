/*
** get_next_line.c for get_next_line in /home/arthur/Documents/B1-C_Graph_Prog/wireframe/src
**
** Made by Arthur Chaloin
** Login   <arthur@epitech.net>
**
** Started on  Tue Nov 22 17:17:21 2016 Arthur Chaloin
** Last update Tue Dec 27 13:41:47 2016 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SIZE	4096

static char	*buffer_to_line(char buffer[BUFF_SIZE])
{
  int		index;
  int		line_len;
  char		*line;

  index = 0;
  while (buffer[index] && buffer[index] != '\n')
    index++;
  line_len = index;
  index = 0;
  if (!(line = malloc(sizeof(char) * (line_len + 1))))
    return (NULL);
  while (index < line_len)
    {
      line[index] = buffer[index];
      index++;
    }
  line[index] = '\0';
  return (line);
}

char		*get_next_line(char *path)
{
  int		fd;
  int		cursor;
  char		buffer[BUFF_SIZE];
  char		*line;
  static int	line_nb = 0;
  static char	*actual = NULL;

  if (!strcmp(path, "reset")) {line_nb = 0; return (NULL);}
  if (!actual) actual = strdup(path);
  else if (strcmp(path, actual)) {actual = path; line_nb = 0;}
  cursor = 0;
  if (!(fd = open(path, O_RDONLY)))
    return (NULL);
  while (cursor < line_nb && read(fd, buffer, 1))
    {
      if (buffer[0] == '\n')
	cursor++;
    }
  buffer[read(fd, buffer, BUFF_SIZE - 1)] = '\0';
  if (!buffer[0])
    return (NULL);
  line = buffer_to_line(buffer);
  line_nb++;
  close(fd);
  return (line);
}
