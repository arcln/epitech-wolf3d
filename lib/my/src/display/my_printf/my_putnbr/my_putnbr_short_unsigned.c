/*
** my_putnbr.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 14:53:50 2016 Arthur Chaloin
** Last update Sun Nov 20 18:58:23 2016 Arthur Chaloin
*/

void	my_putchar(char c);
int	my_strlen(char *str);

int		my_putnbr_short_unsigned(unsigned short int nbr, char *base)
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
