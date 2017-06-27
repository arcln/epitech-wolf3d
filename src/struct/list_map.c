/*
** collect_info.c for my_ls in /home/arthur/Documents/B1-Systeme_UNIX/PSU_2016_my_ls/src/
**
** Made by Arthur Chaloin
** Login   <arthur.chaloin@epitech.eu>
**
** Started on  Tue Nov 29 10:59:57 2016 Arthur Chaloin
** Last update Tue Dec 27 14:02:25 2016 Arthur Chaloin
*/
#include "wolf3d.h"

static int	add_file(t_list **last, struct dirent *actual_file, char *path)
{
  t_file	*file;
  t_list	*new_elem;

  if (!(file = malloc(sizeof(t_file))) ||
      !(new_elem = malloc(sizeof(t_list))))
    return (84);
  new_elem->file = file;
  new_elem->next = NULL;
  new_elem->prev = *last;
  file->name = my_strdup(actual_file->d_name);
  lstat(my_strcat(path, file->name), &(file->info));
  file->type = (S_ISDIR(file->info.st_mode)) ? 'd' :
    (S_ISLNK(file->info.st_mode)) ? 'l' :
    (S_ISFIFO(file->info.st_mode)) ? 'p' :
    (S_ISSOCK(file->info.st_mode)) ? 's' :
    (S_ISCHR(file->info.st_mode)) ? 'c' :
    (S_ISBLK(file->info.st_mode)) ? 'b' : '-';
  if (file->type == 'd')
    file->name = my_strcat(file->name, "/");
  if (*last)
    (*last)->next = new_elem;
  *last = new_elem;
  return (0);
}

t_list		*collect_data(DIR *dir, char *path)
{
  t_list	*files_list;
  t_list	*last;
  struct dirent	*actual_file;

  files_list = NULL;
  last = NULL;
  while ((actual_file = readdir(dir)))
    {
      add_file(&last, actual_file, path);
      if (!files_list)
	files_list = last;
    }
  return (files_list);
}
