/*
** my_strlen.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/string/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 12:21:26 2016 Arthur Chaloin
** Last update Wed Nov 16 12:19:15 2016 Arthur Chaloin
*/

int	my_strlen(char *str)
{
  int	count;

  count = 0;
  while (str[count])
    count++;
  return (count);
}
