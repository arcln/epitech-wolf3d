/*
** my_strcat.c for lib in /home/arthur/Documents/B1-Systeme_UNIX/PSU_2016_my_ls/lib/my/src/string/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Nov 29 18:29:07 2016 Arthur Chaloin
** Last update Fri Dec 23 17:31:06 2016 Arthur Chaloin
*/
#include <stdlib.h>

int	my_strlen(char *str);

char	*my_strcat(char *s1, char *s2)
{
  int	index;
  char	*new;

  index = 0;
  if (!(new = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1))))
    return (NULL);
  while (s1[index])
    {
      new[index] = s1[index];
      index++;
    }
  index = 0;
  while (s2[index])
    {
      new[index + my_strlen(s1)] = s2[index];
      index++;
    }
  new[index + my_strlen(s1)] = '\0';
  return (new);
}
