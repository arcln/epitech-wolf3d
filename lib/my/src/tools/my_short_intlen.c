/*
** my_intlen.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/tools/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Nov 15 13:43:49 2016 Arthur Chaloin
** Last update Sun Nov 20 17:23:24 2016 Arthur Chaloin
*/

int	my_short_intlen(short int nb, int base)
{
  int	count;

  count = 0;
  if (nb == 0)
    return (1);
  while (nb != 0)
    {
      nb /= base;
      count++;
    }
  return (count);
}
