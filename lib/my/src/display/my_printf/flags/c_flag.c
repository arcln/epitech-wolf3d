/*
** u_flag.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Mon Nov 14 09:30:39 2016 Arthur Chaloin
** Last update Thu Nov 24 10:35:26 2016 Arthur Chaloin
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define MINOR_FLAGS	"hlLjzt#0-+. $0123456789"

int	my_putchar(char c);
int	my_putstr(char *str);
int	my_putnstr(char *str, int n);
int	my_strlen(int nb, int base);
int	my_intlen(int nb, int base);
int	my_str_contain(char *str, char c);
int	my_getnbr(char *nb);
int	print_space(int nb);
void	print_zero(int nb);
void	*apply_modifier(char flag, int (*func)());

typedef struct	s_flag_data
{
  char		str;
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
  int		(*func)(char);
}		t_flag_data;

static void	flag_init(t_flag_data *data)
{
  data->cursor = 0;
  data->zero_padded = 0;
  data->plus = 0;
  data->minus = 0;
  data->space = 0;
  data->precision = 0;
  data->alternated = 0;
  data->field_len = 0;
  data->type = 0;
  data->func = &my_putchar;
  data->len_func = &my_strlen;
}

static void	handle_advanced_format(const char *format_flag,
				       t_flag_data *data)
{
  if (format_flag[data->cursor] == '-')
    {
      data->zero_padded = 0;
      data->minus = 1;
    }
  else if (format_flag[data->cursor] == '.')
    {
      data->precision = my_getnbr((char *)format_flag + data->cursor + 1);
      data->cursor += my_intlen(data->precision, 10);
      data->precision = 0;
      data->zero_padded = 0;
    }
}

static void	handle_format(const char *format_flag, t_flag_data *data)
{
  if (my_str_contain(MINOR_FLAGS, format_flag[data->cursor]) == -1)
    return;
  else if (format_flag[data->cursor] > '0' && format_flag[data->cursor] <= '9')
    {
      data->field_len = my_getnbr((char *)format_flag + data->cursor);
      data->cursor += my_intlen(data->field_len, 10) - 1;
    }
  handle_advanced_format(format_flag, data);
}

static int	apply_formats(t_flag_data *data)
{
  if (data->field_len && !data->minus)
    print_space(data->field_len - ((data->precision > 0 &&
				    data->precision < 1) ?
				   data->precision : 1));
  return (0);
}

int		c_flag(va_list *args, const char *format_flag)
{
  t_flag_data	data;

  flag_init(&data);
  while (format_flag[data.cursor] != 'c')
    {
      handle_format(format_flag, &data);
      data.cursor++;
    }
  data.str = va_arg(*args, int);
  data.return_val = apply_formats(&data);
  data.return_val += (data.func)(data.str);
  return ((!data.minus) ? data.return_val : data.return_val + print_space(
          data.field_len - ((data.precision > 0 && data.precision < 1) ?
      				   data.precision : 1)));
}
