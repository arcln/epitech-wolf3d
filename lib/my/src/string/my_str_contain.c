/*
** my_str_contain.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/string/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 12:23:44 2016 Arthur Chaloin
** Last update Wed Nov  9 12:34:58 2016 Arthur Chaloin
*/

int	my_str_contain(char *str, char c)
{
  int	index;

  index = 0;
  while (str[index])
    {
      if (str[index] == c)
	return (index);
      index++;
    }
  return (-1);
}
