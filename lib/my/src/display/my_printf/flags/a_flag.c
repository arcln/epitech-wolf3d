/*
** a_flag.c for lib in /home/arthur/Documents/B1-Systeme_UNIX/PSU_2016_my_printf/src/display/my_printf/flags
**
** Made by Arthur Chaloin
** Login   <arthur@epitech.net>
**
** Started on  Thu Nov 24 09:22:18 2016 Arthur Chaloin
** Last update Thu Nov 24 10:33:10 2016 Arthur Chaloin
*/
#include <unistd.h>
#include <stdarg.h>

int	my_printf(const char *format, ...);
void	bad_flag();

void	show_str_tab(va_list *ap, char *flag)
{
  int	index;
  int	size;
  char	**map;

  index = 0;
  map = va_arg(*ap, char**);
  size = va_arg(*ap, int);
  while (index < size)
    {
      my_printf(flag, map[index]);
      index++;
    }
}

void	show_int_tab(va_list *ap, char *flag)
{
  int	index;
  int	size;
  int	*map;

  index = 0;
  map = va_arg(*ap, int*);
  size = va_arg(*ap, int);
  while (index < size)
    {
      my_printf(flag, map[index]);
      index++;
    }
}

int	a_flag(va_list *ap, const char *format)
{
  char	flag[4];
  char	separator;
  void	(*func)();

  separator = format[1];
  if (format[2] == 'i')
    func = &show_int_tab;
  else
    func = &show_str_tab;
  flag[0] = '%';
  flag[1] = format[2];
  flag[2] = separator;
  flag[3] = '\0';
  if (format[2] == 'i')
    func(ap, flag);
  else if (format[2] == 's')
    func(ap, flag);
  write(1, "\b", 1);
  return (0);
}
