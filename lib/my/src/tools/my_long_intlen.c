/*
** my_intlen.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/tools/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Nov 15 13:43:49 2016 Arthur Chaloin
** Last update Sat Nov 19 11:18:06 2016 Arthur Chaloin
*/

int	my_long_intlen(long int nb, int base)
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
