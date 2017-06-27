/*
** my_strnbr.c for lib in /home/arthur/Documents/lib/my/src/tools/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Fri Dec 23 17:31:36 2016 Arthur Chaloin
** Last update Fri Dec 23 17:40:55 2016 Arthur Chaloin
*/
#include <stdlib.h>

int	my_intlen(int nb, int base);

static void	core(int nb, char *nb_str)
{
  if (nb < 0)
    *nb_str = '-';
  if (nb / 10 != 0)
    core((nb < 0 ? nb / 10 * -1 : nb / 10), &nb_str[-1]);
  nb_str[0] = '0' + (nb < 0 ? nb % 10 * -1 : nb % 10);
}

char	*my_strnbr(int nb)
{
  char	*nb_str;

  if (!(nb_str = malloc(sizeof(char) * (my_intlen(nb, 10) + 1))))
    return (NULL);
  core(nb, &nb_str[my_intlen(nb, 10) - 1]);
  nb_str[my_intlen(nb, 10)] = '\0';
  return (nb_str);
}
