/*
** my_putstr.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 12:08:53 2016 Arthur Chaloin
** Last update Sat Nov 19 19:44:06 2016 Arthur Chaloin
*/
#include <unistd.h>

int	my_strlen(char *str);

int	my_putnstr(char *str, int n)
{
  if (str == NULL)
    write(1, "(null)", 6);
  else
    write(1, str, (n > my_strlen(str) ? my_strlen(str) : n));
  return ((str == NULL) ? 6 : my_strlen(str));
}
