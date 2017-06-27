/*
** my_strdup.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/string/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sun Nov 20 14:51:34 2016 Arthur Chaloin
** Last update Sun Nov 20 17:37:43 2016 Arthur Chaloin
*/
#include <stdlib.h>

int	my_strlen(char *str);

char	*my_strdup(char *copy)
{
  int	index;
  char	*new_str;

  index = 0;
  if (copy == NULL ||
      !(new_str = malloc(sizeof(char) * (my_strlen(copy) + 1))))
    return (NULL);
  while (copy[index])
    {
      new_str[index] = copy[index];
      index++;
    }
  new_str[index] = 0;
  return (new_str);
}
