/*
** my_putnbr.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 14:53:50 2016 Arthur Chaloin
** Last update Sun Nov 20 18:55:04 2016 Arthur Chaloin
*/

int	my_putchar(char c);
int	my_strlen(char *str);
int	my_putstr(char *str);

static int	negative_test(long int nbr, int *printed)
{
  if (nbr < 0)
    {
      nbr = -nbr;
      my_putchar('-');
      (*printed)++;
      return (nbr);
    }
  else
    return (nbr);
}

int		my_putnbr(int nbr, char *base)
{
  int		printed;
  int		baselen;
  long int	power;

  power = 1;
  printed = 0;
  baselen = my_strlen(base);
  if (nbr == -2147483648)
    my_putstr("2147483648");
  else if (nbr == 0)
    my_putchar(base[0]);
  else
    {
      nbr = negative_test(nbr, &printed);
      while (nbr / power > 0)
        power *= baselen;
      power /= baselen;
      while (power > 0)
        {
          my_putchar(base[(nbr / power) % baselen]);
          power /= baselen;
          printed++;
	}
    }
  return (printed);
}
