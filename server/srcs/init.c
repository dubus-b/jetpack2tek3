/*
** init.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016/server/srcs
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Sun Jul 16 11:21:27 2017 Clary Arthur
** Last update Tue Jul 18 16:03:52 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void		alloc_map(t_data *data)
{
  int		idx;

  if ((data->Map = malloc(sizeof(char *) * (data->height_map + 1))) == NULL)
    exit(84);
  idx = 0;
  while (idx < data->height_map)
    {
      if ((data->Map[idx] = malloc(sizeof(char)
				   * (data->length_map + 1))) == NULL)
	exit(84);
      idx = idx + 1;
    }
}

void		init_clt(t_data *data, t_player *clt)
{
  clt->fd_clt = 0;
  clt->score = 0;
  clt->haveID = 0;
  clt->haveMAP = 0;
  clt->isREADY = 0;
  clt->isFIRE = 0;
  clt->y = data->height_map / 2;
}

void		init_game(t_data *data)
{
  int		i;

  data->max_fd = data->fd_socket;
  data->x = 0;
  data->nb_clt = 0;
  if (g_GameRun == 0)
    {
      alloc_map(data);
      if ((data->p1 = malloc(sizeof(t_player))) == NULL)
	exit(84);
      if ((data->p2 = malloc(sizeof(t_player))) == NULL)
	exit(84);
    }
  i = data->height_map - 1;
  while (i >= 0)
    {
      data->Map[i] = strdup(data->savMap[i]);
      i = i - 1;
    }
  g_GameRun = 0;
  init_clt(data, data->p1);
  init_clt(data, data->p2);
}
