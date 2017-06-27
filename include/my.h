/*
** my.h for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/include/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Wed Nov  9 11:14:39 2016 Arthur Chaloin
** Last update Sat Dec 24 15:45:52 2016 Arthur Chaloin
*/

#ifndef MY_H_
# define MY_H_

int	my_printf(const char *format, ...);
int	my_strlen(char *str);
int	my_tablen(char **tab);
int	my_str_contain(char *str, char c);
int	my_getnbr(char *str);
int	my_intlen(int nb, int base);
char	*my_strdup(char *str);
char	*my_strcat(char *s1, char *s2);
char	*my_strnbr(int nb);
char	**my_tabdup(char **tab);
char	**map_file(char *path);

#endif /* !MY_H_ */
