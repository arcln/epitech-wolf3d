/*
** my_printf.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 11:13:39 2016 Arthur Chaloin
** Last update Thu Nov 24 10:25:55 2016 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAJOR_FLAGS	"diouxXbcsSpmna%"

int	my_putchar(char c);
int	my_putstr(char *str);
int	my_putnbr(int nb, char *base);
int	my_str_contain(char *str, char c);
int	my_strlen(char *str);
int	my_intlen(int nb, int base);
char	*my_strdup(char *str);
int	bad_flag();
int	check_flag(const char *flag, char final);
int	d_flag(va_list *args, const char *format_flag);
int	o_flag(va_list *args, const char *format_flag);
int	u_flag(va_list *args, const char *format_flag);
int	x_flag(va_list *args, const char *format_flag);
int	xx_flag(va_list *args, const char *format_flag);
int	s_flag(va_list *args, const char *format_flag);
int	ss_flag(va_list *args, const char *format_flag);
int	c_flag(va_list *args, const char *format_flag);
int	p_flag(va_list *args, const char *format_flag);
int	b_flag(va_list *args, const char *format_flag);
int	a_flag(va_list *args, const char *format_flag);
int	percent_flag(va_list *args, const char *format_flag);

int	size_printed;

typedef int	(*t_func)(va_list*, const char*);

static t_func		*init_call_tab()
{
  int			index;
  static t_func		call[256];

  index = 0;
  while (index < 256)
    {
      call[index] = &bad_flag;
      index++;
    }
  call['a'] = &a_flag;
  call['d'] = &d_flag;
  call['i'] = &d_flag;
  call['o'] = &o_flag;
  call['u'] = &u_flag;
  call['x'] = &x_flag;
  call['X'] = &xx_flag;
  call['s'] = &s_flag;
  call['S'] = &ss_flag;
  call['c'] = &c_flag;
  call['p'] = &p_flag;
  call['b'] = &b_flag;
  call['%'] = &percent_flag;
  return (call);
}

static int	call_flag(va_list *args, const char *format, int *index)
{
  int		level;
  int		cursor;
  t_func	*call;

  call = init_call_tab();
  cursor = 1;
  level = 0;
  while ((format[*index + cursor] &&
	  my_str_contain(MAJOR_FLAGS, format[*index + cursor]) == -1) ||
	 level != 0)
    {
      level = (format[*index + cursor] == '(') ? level + 1 : level;
      level = (format[*index + cursor] == ')') ? level - 1 : level;
      cursor++;
    }
  if (!format[*index + cursor])
    return (-1);
  if (format[*index + cursor] != 'a' &&
      check_flag(format + *index, format[*index + cursor]))
    return (-1);
  *index += cursor;
  return (call[(int)format[*index]](args, format + *index - cursor + 1) + 666);
}

int			my_printf(const char *format, ...)
{
  int			index;
  int			result;
  va_list		args;

  index = 0;
  size_printed = 0;
  va_start(args, format);
  while (format[index])
    {
      if ((format[index] == '%') &&
	  (result = call_flag(&args, format, &index) != -1))
	size_printed += result;
      else
	my_putchar(format[index]);
      size_printed++;
      index++;
    }
  va_end(args);
  return (size_printed);
}
