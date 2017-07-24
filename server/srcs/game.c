/*
** game.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016/server
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Sun Jul 16 15:04:14 2017 Clary Arthur
** Last update Mon Jul 17 18:03:59 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void		end_game(t_data *data, int flag_why)
{
  char		buff[100];
  int		fd_win;

  if (flag_why == 0)
    {
      if (data->p1->score > data->p2->score)
	fd_win = data->p1->fd_clt;
      else if (data->p2->score > data->p1->score)
	fd_win = data->p2->fd_clt;
      if (data->p1->score == data->p2->score)
	fd_win = -1;
    }
  else if (flag_why > 0)
    fd_win = flag_why;
  memset(buff, 0, 100);
  sprintf(buff, "FINISH %d\n", fd_win);
  write(data->p1->fd_clt, buff, strlen(buff));
  write(data->p2->fd_clt, buff, strlen(buff));
  init_game(data);
}

void		search_strike(t_data *data, t_player *clt)
{
  int		posx_clt;
  int		posy_clt;
  char		buff[100];

  posx_clt = data->x;
  posy_clt = clt->y;
  memset(buff, 0, 100);
  if (data->Map[posy_clt][posx_clt] == 'e')
    {
      if (clt == data->p1)
	end_game(data, data->p2->fd_clt);
      else if (clt == data->p2)
	end_game(data, data->p1->fd_clt);
    }
  else if (data->Map[posy_clt][posx_clt] == 'c')
    {
      sprintf(buff, "COIN %d %d %d\n", clt->fd_clt, posx_clt, posy_clt);
      write(data->p1->fd_clt, buff, strlen(buff));
      write(data->p2->fd_clt, buff, strlen(buff));
      clt->score = clt->score + 1;
      data->Map[posy_clt][posx_clt] = '_';
    }
}

void		send_status(t_data *data)
{
  char		status_p1[100];
  char		status_p2[100];

  memset(status_p1, 0, 100);
  sprintf(status_p1, "PLAYER %d %f %f %d\n", data->p1->fd_clt,
	  data->x, data->p1->y, data->p1->score);
  memset(status_p2, 0, 100);
  sprintf(status_p2, "PLAYER %d %f %f %d\n", data->p2->fd_clt,
	  data->x, data->p2->y, data->p2->score);
  write(data->p1->fd_clt, status_p1, strlen(status_p1));
  write(data->p1->fd_clt, status_p2, strlen(status_p2));
  write(data->p2->fd_clt, status_p1, strlen(status_p1));
  write(data->p2->fd_clt, status_p2, strlen(status_p2));
}

void		calc_y(t_data *data, t_player *clt)
{
  if (clt->isFIRE == 0)
    clt->y = clt->y + (0.000021 * data->_gravity);
  else if (clt->isFIRE == 1)
    clt->y = clt->y + (0.000021 * data->_gravity * (-1));
  if (clt->y <= 0)
    clt->y = 0;
  else if (clt->y >= data->height_map - 1)
    clt->y = data->height_map - 1;
}
