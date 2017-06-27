/*
** my_showstr.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 16:40:07 2016 Arthur Chaloin
** Last update Sat Nov 19 20:35:16 2016 Arthur Chaloin
*/
#include <unistd.h>

int	my_putchar(char c);
int	my_putstr(char *str);
int	my_putnbr(int nb, char *base);

static void	my_show_unprintable(char c)
{
  my_putchar('\\');
  if (c < 8)
    {
      my_putchar('0');
      my_putchar('0');
      my_putnbr((int)c, "01234567");
    }
  else if (c < 32)
    {
      my_putchar('0');
      my_putnbr((int)c, "01234567");
    }
  else
    my_putnbr((int)c, "01234567");
}

int	my_shownstr(char *str, int n)
{
  int	index;

  index = 0;
  if (str == NULL)
    {
      my_putstr("(null)");
      return (6);
    }
  while (str[index] && index < n)
    {
      if (str[index] < 32 || str[index] >= 127)
	my_show_unprintable(str[index]);
      else
	my_putchar(str[index]);
      index++;
    }
  return (index);
}
