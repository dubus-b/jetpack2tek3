/*
** utility.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Thu Jul 13 17:20:36 2017 Clary Arthur
** Last update Tue Jul 18 18:05:16 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void		get_sigint(int signal)
{
  if (g_GameRun == 2)
    exit(0);
  g_GameRun = 2;
  signal = signal;
}

int		get_arg(t_data *data, int ac, char **av, int isFind)
{
  int		opt;

  opt = 0;
  while ((opt = getopt(ac, av, "p:g:m:")) != -1)
    {
      if (opt == 'p')
	{
	  data->_port = atoi(optarg);
	  isFind = isFind + 2;
	}
      else if (opt == 'g')
	{
	  data->_gravity = atoi(optarg);
	  isFind = isFind + 3;
	}
      else if (opt == 'm')
	{
	  data->_map = optarg;
	  isFind = isFind + 4;
	}
    }
  if (isFind == 9)
    return (0);
  return (1);
}

void		exit_error(char *arg)
{
  fprintf(stderr, "%s\n", arg);
  exit(84);
}

void		free_all(t_data *data, t_Manag *Manag)
{
  int		idx;

  free(Manag);
  free(data->p1);
  free(data->p2);
  idx = 0;
  while (idx < data->height_map)
    {
      free(data->Map[idx]);
      free(data->savMap[idx]);
      idx = idx + 1;
    }
  free(data->Map);
  free(data->savMap);
}

void		close_all(t_data *data)
{
  close(data->fd_socket);
  if (data->nb_clt >= 1)
    close(data->p1->fd_clt);
  if (data->nb_clt == 2)
  close(data->p2->fd_clt);
}
