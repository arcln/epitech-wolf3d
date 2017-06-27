/*
** my_tabcy.c for lib in /home/arthur/Documents/lib/my/src/string/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Dec  6 14:45:08 2016 Arthur Chaloin
** Last update Mon Dec 19 18:53:35 2016 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>

char	*my_strdup(char *str);
int	my_tablen(char **tab);

char	**my_tabdup(char **tab)
{
  int		index;
  char		**new;

  index = 0;
  if (!(new = malloc(sizeof(char *) * (my_tablen(tab) + 1))))
    return (NULL);
  while (index < my_tablen(tab))
    {
      new[index] = my_strdup(tab[index]);
      index++;
    }
  new[index] = NULL;
  return (new);
}
