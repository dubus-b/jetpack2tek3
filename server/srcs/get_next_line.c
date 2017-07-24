/*
** get_next_line.c for Project-Master in /home/bdubus/jetpack2Tek3_2016
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Fri Jul 14 14:36:34 2017 Benjamin Dubus
** Last update Mon Jul 17 14:47:10 2017 Clary Arthur
*/

#include "srv_jetpack.h"

void    *xmalloc(size_t size)
{
  void  *tmp;

  tmp = malloc(size);
  if (!tmp)
    exit(1);
  return (tmp);
}

char	*my__strcat(char *str, char buff)
{
  size_t	i;
  char		*final;

  i = 0;
  if (!(final = xmalloc(strlen(str) + 2)))
    return (0);
  while (i < strlen(str))
    {
      final[i] = str[i];
      i = i + 1;
    }
  final[i] = buff;
  final[i + 1] = '\0';
  if (str && str[0] != 0)
    free(str);
  return (final);
}

int	finalise(char **unsent, char *buff, int i, int rc)
{
  i = i + 1;
  while (i < rc)
    {
      *unsent = my__strcat(*unsent, buff[i]);
      i = i + 1;
    }
  return (0);
}

char	*get_unsent(char **unsent, int *ret)
{
  char	*str;

  str = "";
  while (*unsent[0] && *unsent[0] != '\n')
    {
      str = my__strcat(str, *unsent[0]);
      *unsent = *unsent + 1;
    }
  if (*unsent[0])
    {
      *unsent = *unsent + 1;
      *ret = 1;
    }
  return (str);
}

char		*get_next_line(int fd)
{
  char		*buff;
  char		*str;
  int		i;
  int		j;
  int		rc;
  static char	*unsent = "";

  i = 0;
  str = get_unsent(&unsent, &i);
  if (i || (i = 0))
    return (str);
  if (!(buff = xmalloc(126 * sizeof(char))))
    return (0);
  while ((rc = (read(fd, buff, 126) + (j = 0))))
    while (j < rc + 0 * (i = i + 1))
      {
	if (buff[j] == '\n')
	  return (str + finalise(&unsent, buff, j, rc));
	if (!(str = my__strcat(str, buff[j])))
	  return (0);
	j = j + 1;
      }
  if (!str[0])
    return (0);
  return (str);
}
