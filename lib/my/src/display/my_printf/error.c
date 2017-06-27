/*
** error.c for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/src/display/my_printf/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Sun Nov 20 17:01:10 2016 Arthur Chaloin
** Last update Thu Nov 24 10:35:01 2016 Arthur Chaloin
*/
#define MINOR_FLAGS	"hlLjzt#0-+. $0123456789()"
#define GROUP_A		"0#+- $()"
#define GROUP_B		"123456789$()"
#define GROUP_C		".$()"
#define GROUP_D		"hlLjzt$()"

int	my_intlen(int nb, int base);
int	my_getnbr(char *nb);
int	my_str_contain(char *str, char c);
char	*my_strdup(char *str);

typedef struct	s_error
{
  int		cursor;
  int		group;
  int		new;
  char		*flags_used;
}		t_error;

int	bad_flag()
{
  return (-1);
}

static void	init_error(t_error *data)
{
  data->cursor = 1;
  data->group = 0;
  data->flags_used = my_strdup("0000");
}

static int	get_group(char c)
{
  if (my_str_contain(GROUP_A, c) != -1)
    return (1);
  else if (my_str_contain(GROUP_B, c) != -1)
    return (2);
  else if (my_str_contain(GROUP_C, c) != -1)
    return (3);
  else if (my_str_contain(GROUP_D, c) != -1)
    return (4);
  return (-1);
}

static void	update_levels(t_error *data, const char *flag)
{
  if (data->new == 2)
    {
      data->cursor += my_intlen(my_getnbr((char*)flag + data->cursor), 10) - 1;
      data->flags_used[0] += 1;
    }
  if (data->new == 3)
    {
      if (flag[data->cursor + 1] >= '0' && flag[data->cursor + 1] <= '9')
        data->cursor += my_intlen(my_getnbr((char*)flag + data->cursor + 1),
				  10);
      data->flags_used[1] += 1;
    }
  if (flag[data->cursor] == 'l')
    data->flags_used[3] += 1;
  if (flag[data->cursor] == 'h')
    data->flags_used[4] += 1;
}

int		check_flag(const char *flag, char final)
{
  t_error	data;

  init_error(&data);
  while (flag[data.cursor] != final)
    {
      if ((data.new = get_group(flag[data.cursor])) < data.group)
	return (1);
      update_levels(&data, flag);
      if (data.flags_used[0] > '1' || data.flags_used[1] > '1' ||
	  data.flags_used[2] > '2' || data.flags_used[3] > '2')
	return (1);
      data.group = data.new;
      data.cursor++;
    }
  return (0);
}
