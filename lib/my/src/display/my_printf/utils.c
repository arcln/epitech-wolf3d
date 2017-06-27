/*
** utils.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Nov 15 14:03:13 2016 Arthur Chaloin
** Last update Sat Nov 19 18:10:50 2016 Arthur Chaloin
*/

int	my_putchar(char c);

void	print_zero(int nb)
{
  int	count;

  count = 0;
  while (count < nb)
    {
      my_putchar('0');
      count++;
    }
}

int	print_space(int nb)
{
  int	count;

  count = 0;
  while (count < nb)
    {
      my_putchar(' ');
      count++;
    }
  return (nb);
}
