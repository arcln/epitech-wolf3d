/*
** my_putchar.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 11:12:31 2016 Arthur Chaloin
** Last update Fri Nov 11 10:49:21 2016 Arthur Chaloin
*/
#include <unistd.h>

int	my_putchar(char c)
{
  write(1, &c, 1);
  return (1);
}
