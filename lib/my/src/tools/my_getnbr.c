/*
** my_getnbr.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/tools/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Nov 15 13:46:23 2016 Arthur Chaloin
** Last update Sun Nov 20 19:13:14 2016 Arthur Chaloin
*/

static int	is_max(char *str, int iterator)
{
  char		*max;
  int		iterator2;

  max = "2147483648";
  iterator2 = 0;
  while (iterator2 <= 9)
    {
      if (str[iterator + iterator2] != max[iterator2])
	return (0);
      iterator2 += 1;
    }
  return (1);
}

static int	get_sign(char *str, int *iterator, int *is_neg)
{
  while (!('0' <= str[*iterator] && str[*iterator] <= '9'))
    {
      if (str[*iterator] != '+' && str[*iterator] != '-')
	return (0);
      if (str[*iterator] == '-')
	{
	  if (*is_neg == 0)
	    *is_neg = 1;
	  else
	    *is_neg = 0;
	}
      *iterator += 1;
    }
  return (0);
}

int	my_getnbr(char *str)
{
  int	iterator;
  int	nbr;
  int	is_neg;

  is_neg = 0;
  iterator = 0;
  nbr = 0;
  get_sign(str, &iterator, &is_neg);
  if (is_max(str, iterator))
    return (-2147483648);
  while ('0' <= str[iterator] && str[iterator] <= '9')
    {
      nbr = nbr * 10 + str[iterator] - 48;
      if (nbr < 0)
	return (0);
      iterator += 1;
    }
  if (is_neg)
    nbr *= -1;
  return (nbr);
}
