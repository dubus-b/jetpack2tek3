/*
** get_map.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016/server
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Fri Jul 14 18:13:02 2017 Clary Arthur
** Last update Tue Jul 18 15:37:14 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void		recup_tab_map(t_data *data, char *map, int kdx)
{
  int		idx;
  int		jdx;

  if ((data->savMap = malloc(sizeof(char *) * (data->height_map + 1))) == NULL)
    exit(84);
  idx = 0;
  while (idx < data->height_map)
    {
      if ((data->savMap[idx] = malloc(sizeof(char)
				   * (data->length_map + 1))) == NULL)
	exit(84);
      idx = idx + 1;
    }
  idx = data->height_map - 1;
  while (idx >= 0)
    {
      jdx = 0;
      while (jdx < data->length_map)
	{
	  data->savMap[idx][jdx] = map[kdx];
	  jdx = jdx + 1;
	  kdx = kdx + 1;
	}
      idx = idx - 1;
    }
}

void		valid_map(char *map)
{
  int		len;
  int		wid;
  int		len_tmp;
  int		i;

  len = 0;
  wid = 0;
  i = 0;
  while (map[i] != '\0')
    {
      if (wid == 0 && map[i] != '\n')
	len = len + 1;
      else if (map[i] != '\n')
	len_tmp = len_tmp + 1;
      else if (map[i] == '\n')
	{
	  if (wid != 0 && len != len_tmp)
	    exit_error("Map invalide");
	  wid = wid + 1;
	  len_tmp = 0;
	}
      if (map[i] != '_' && map[i] != 'e' && map[i] != 'c' && map[i] != '\n')
	exit_error("Map invalide");
      i = i + 1;
    }
}

void		eject_endline(t_data *data, char *map, int len, int wid)
{
  int		idx;
  int		jdx;
  char		*tmp;

  idx = 0;
  jdx = 0;
  tmp = 0;
  if ((tmp = malloc(sizeof(char) * (len * wid))) == NULL)
    return;
  while (map[idx] != '\0')
    {
      if (map[idx] != '\n')
	{
	  tmp[jdx] = map[idx];
	  jdx = jdx + 1;
	}
      idx = idx + 1;
    }
  memset(data->_map, 0, strlen(tmp));
  sprintf(data->_map, "MAP %d %d %s\n", len, wid, tmp);
  recup_tab_map(data, tmp, 0);
  free(tmp);
}

int		check_map(t_data *data, char *map)
{
  int		length;
  int		width;
  int		idx;

  length = 0;
  width = 0;
  idx = 0;
  valid_map(map);
  while (map[idx] != '\0')
    {
      if (width == 0 && map[idx] != '\n')
	length = length + 1;
      else if (map[idx] == '\n')
	width = width + 1;
      idx = idx + 1;
    }
  data->height_map = width;
  data->length_map = length;
  eject_endline(data, map, length, width);
  return (0);
}

int		get_map(t_data *data, char *file)
{
  int		fd;
  struct stat	sb;
  char		*buff;

  if ((fd = open(file, O_RDONLY)) == -1)
    exit_error("Map invalide");
  stat(file, &sb);
  if ((buff = malloc(sizeof(char) * sb.st_size)) == NULL)
    return (-1);
  if ((read(fd, buff, sb.st_size)) == -1)
    return (-1);
  close(fd);
  check_map(data, buff);
  return (0);
}
