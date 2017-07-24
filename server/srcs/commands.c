/*
** command.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016/server/srcs
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Sat Jul 15 16:19:56 2017 Clary Arthur
** Last update Mon Jul 17 16:01:24 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void		_id(t_data *data, t_player *clt)
{
  char		buff[100];

  data = data;
  clt->haveID = 1;
  memset(buff, 0, 100);
  sprintf(buff, "ID %d\n", clt->fd_clt);
  write(clt->fd_clt, buff, strlen(buff));
}

void		_map(t_data *data, t_player *clt)
{
  clt->haveMAP = 1;
  write(clt->fd_clt, data->_map, strlen(data->_map));
}

void		_ready(t_data *data, t_player *clt)
{
  data = data;
  if (clt->haveID == 1 && clt->haveMAP == 1)
    clt->isREADY = 1;
}

void		_activ_fire(t_data *data, t_player *clt)
{
  data = data;
  clt->isFIRE = 1;
}

void		_desactiv_fire(t_data *data, t_player *clt)
{
  data = data;
  clt->isFIRE = 0;
}
