/*
** my_putnbr.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 14:53:50 2016 Arthur Chaloin
** Last update Sun Nov 20 17:23:32 2016 Arthur Chaloin
*/

void	my_putchar(char c);
int	my_strlen(char *str);

static short int	negative_test(short int nbr, int *printed)
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

int		my_putnbr_short(short int nbr, char *base)
{
  int		printed;
  int		baselen;
  int		i;
  long long int	power;

  power = 1;
  printed = 0;
  baselen = my_strlen(base);
  if (nbr == 0)
    {
      my_putchar(base[0]);
      return (0);
    }
  nbr = negative_test(nbr, &printed);
  while (nbr / power > 0)
    power *= baselen;
  power /= baselen;
  while (power > 0)
    {
      i = (nbr / power) % baselen;
      my_putchar(base[i]);
      power /= baselen;
      printed++;
    }
  return (printed);
}
