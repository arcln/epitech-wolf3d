/*
** u_flag.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Nov 14 09:30:39 2016 Arthur Chaloin
** Last update Sun Nov 20 19:28:24 2016 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define MINOR_FLAGS	"hlLjzt#0-+. $0123456789"

int	my_putchar(char c);
int	my_putstr(char *str);
int	my_putnbr_unsigned(int nbr, char *base);
int	my_putnbr_long_unsigned(int nbr, char *base);
int	my_intlen(int nb, int base);
int	my_long_intlen(int nb, int base);
int	my_str_contain(char *str, char c);
int	my_getnbr(char *nb);
int	print_space(int nb);
void	print_zero(int nb);
void	*apply_modifier(char flag, int (*func)());

typedef struct	s_flag_data
{
  long int	nb;
  int		cursor;
  int		zero_padded;
  int		field_len;
  int		space;
  int		plus;
  int		minus;
  int		precision;
  int		return_val;
  int		alternated;
  int		type;
  int		(*len_func)();
  int		(*func)();
}		t_flag_data;

static void	flag_init(t_flag_data *data)
{
  data->cursor = 0;
  data->zero_padded = 0;
  data->plus = 0;
  data->minus = 0;
  data->space = 0;
  data->precision = 0;
  data->alternated = 2;
  data->field_len = 0;
  data->type = 0;
  data->func = &my_putnbr_unsigned;
  data->len_func = &my_long_intlen;
}

static void	handle_advanced_format(const char *format_flag,
				       t_flag_data *data)
{
  if (format_flag[data->cursor] == ' ' && !data->plus)
    data->space = 1;
  else if (format_flag[data->cursor] == '+')
    {
      data->plus = 1;
      data->space = 0;
    }
  else if (format_flag[data->cursor] == '#')
    data->alternated = 2;
  else if (format_flag[data->cursor] == '-')
    {
      data->zero_padded = 0;
      data->minus = 1;
    }
  else if (format_flag[data->cursor] == '.')
    {
      if (format_flag[data->cursor + 1] >= '0' &&
	  format_flag[data->cursor + 1] <= '9')
	{
          data->precision = my_getnbr((char *)format_flag + data->cursor + 1);
          data->cursor += data->len_func(data->precision, 10);
  	}
      data->zero_padded = 0;
    }
}

static void	handle_format(const char *format_flag, t_flag_data *data)
{
  if (my_str_contain(MINOR_FLAGS, format_flag[data->cursor]) == -1)
    return;
  else if (format_flag[data->cursor] == '0' && !data->minus)
    data->zero_padded = 1;
  else if (format_flag[data->cursor] > '0' && format_flag[data->cursor] <= '9')
    {
      data->field_len = my_getnbr((char *)format_flag + data->cursor);
      data->cursor += data->len_func(data->field_len, 10) - 1;
    }
  else if (format_flag[data->cursor] == 'l')
    {
      data->func = &my_putnbr_long_unsigned;
      data->len_func = &my_long_intlen;
      data->type = 1;
    }
  handle_advanced_format(format_flag, data);
}

static int	apply_formats(t_flag_data *data)
{
  if (data->nb < 0)
    {
      data->field_len--;
      data->plus = 0;
      data->space = 0;
    }
  data->precision -= (data->precision > 0) ? data->len_func(data->nb, 16) : 0;
  if (data->field_len && !data->minus && !data->zero_padded)
    print_space(data->field_len - data->len_func(data->nb, 16)
		- ((data->precision > 0) ? data->precision : 0)
		- ((data->precision > 0) ? 0 : data->alternated));
  if (data->nb < 0 && my_putchar('-'))
      data->nb = -data->nb;
  if (data->alternated)
      my_putstr("0x");
  if (data->precision)
    print_zero(data->precision - data->alternated);
  if (data->zero_padded && data->precision <= 0)
    {
      print_zero(data->field_len - data->len_func(data->nb, 16)
		  - ((data->precision > 0) ? data->precision : 0)
        	  - ((data->precision > 0) ? 0 : data->alternated));
    }
  return (0);
}

int		p_flag(va_list *args, const char *format_flag)
{
  t_flag_data	data;

  flag_init(&data);
  while (format_flag[data.cursor] != 'p')
    {
      handle_format(format_flag, &data);
      data.cursor++;
    }
  if (data.type)
    data.nb = va_arg(*args, unsigned long int);
  else
    data.nb = va_arg(*args, unsigned int);
  if (data.nb == 0)
    {
      my_putstr("(nil)");
      return (0);
    }
  data.return_val = apply_formats(&data);
  data.return_val += (data.func)(data.nb, "0123456789abcdef");
  return ((!data.minus) ? data.return_val : data.return_val + print_space(
	  data.field_len - data.len_func(data.nb, 16)
	   - ((data.precision > 0) ? 0 : data.alternated)
	   - ((data.precision > 0) ? data.precision : 0)));
}
