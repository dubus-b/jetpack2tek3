/*
** main.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Thu Jul 13 11:41:30 2017 Clary Arthur
** Last update Tue Jul 18 18:08:37 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void			play_game(t_data *data)
{
  send_status(data);
  search_strike(data, data->p1);
  search_strike(data, data->p2);
  if (data->x >= data->length_map)
    end_game(data, 0);
  data->x = data->x + 0.000271;
  calc_y(data, data->p1);
  calc_y(data, data->p2);
  usleep(10);
}

void			reset_fd(t_data *data)
{
  FD_ZERO(&data->read_set);
  FD_ZERO(&data->write_set);
  FD_SET(data->fd_socket, &data->read_set);
  FD_SET(data->fd_socket, &data->write_set);
  if (data->nb_clt >= 1)
    {
      FD_SET(data->p1->fd_clt, &data->read_set);
      FD_SET(data->p1->fd_clt, &data->write_set);
      if (data->nb_clt == 2)
	{
	  FD_SET(data->p2->fd_clt, &data->read_set);
	  FD_SET(data->p2->fd_clt, &data->write_set);
	}
    }
  if (data->max_fd < data->p1->fd_clt)
    data->max_fd = data->p1->fd_clt;
  else if (data->max_fd < data->p2->fd_clt)
    data->max_fd = data->p2->fd_clt;
}

void			check_fd(t_data *data, t_Manag *Manag)
{
  if ((FD_ISSET(data->fd_socket, &data->read_set) == 1)
      && (data->nb_clt == 0))
    data->p1->fd_clt = get_client(data);
  else if ((FD_ISSET(data->fd_socket, &data->read_set) == 1)
	   && (data->nb_clt == 1))
    data->p2->fd_clt = get_client(data);
  if ((data->nb_clt >= 1) &&
      (FD_ISSET(data->p1->fd_clt, &data->read_set) == 1))
    interpret(data, data->p1, Manag);
  else if ((data->nb_clt >= 2) &&
	   (FD_ISSET(data->p2->fd_clt, &data->read_set) == 1))
    interpret(data, data->p2, Manag);
}

void			run_game(t_data *data)
{
  struct timeval	time;
  t_Manag		*Manag;

  time.tv_sec = 60;
  time.tv_usec = 0;
  g_GameRun = 0;
  Manag = 0;
  init_game(data);
  Manag = init_Manag(Manag);
  while (g_GameRun == 0 || g_GameRun == 1)
    {
      reset_fd(data);
      if (select(data->max_fd + 1, &data->read_set,
		 &data->write_set, NULL, &time) == -1)
	g_GameRun = -1;
      check_fd(data, Manag);
      if (g_GameRun == 1)
	play_game(data);
    }
  if (g_GameRun == 2)
    {
      write(data->p1->fd_clt, "FINISH -1\n", strlen("FINISH -1\n"));
      write(data->p2->fd_clt, "FINISH -1\n", strlen("FINISH -1\n"));
    }
  free_all(data, Manag);
}

int			main(int ac, char **av)
{
  t_data		data;

  signal(SIGINT, get_sigint);
  if ((get_arg(&data, ac, av, 0)) == 1)
    exit_error("Arguments invalides");
  get_map(&data, data._map);
  if ((data.fd_socket = make_socket(data._port)) == -1)
    exit(84);
  run_game(&data);
  close_all(&data);
  return (0);
}
