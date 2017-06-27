/*
** my_tablen.c for lib in /home/arthur/Documents/lib/my/src/string/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Dec  6 10:18:22 2016 Arthur Chaloin
** Last update Tue Dec  6 10:19:04 2016 Arthur Chaloin
*/

int	my_tablen(char **tab)
{
  int	count;

  count = 0;
  while (tab[count])
    count++;
  return (count);
}
