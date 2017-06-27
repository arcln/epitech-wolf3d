/*
** percent_flag.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/flags/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sat Nov 19 20:50:25 2016 Arthur Chaloin
** Last update Sat Nov 19 20:53:07 2016 Arthur Chaloin
*/
#include <stdarg.h>

int	my_putchar(char c);

int	percent_flag(va_list *args, const char *format_flag)
{
  int	cursor;

  cursor = 0;
  (void)args;
  while (format_flag[cursor] != '%')
    cursor++;
  return (my_putchar('%'));
}
