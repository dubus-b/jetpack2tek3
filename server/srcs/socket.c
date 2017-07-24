/*
** socket.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Thu Jul 13 11:40:30 2017 Clary Arthur
** Last update Tue Jul 18 18:13:34 2017 Clary Arthur
*/

# include "srv_jetpack.h"

void			remove_clt(t_data *data, t_player *clt)
{
  char			buff[100];

  if (data->nb_clt == 2 && g_GameRun == 1)
    {
      memset(buff, 0, 100);
      if (clt == data->p1)
  	{
  	  sprintf(buff, "FINISH %d\n", data->p2->fd_clt);
  	  write(data->p2->fd_clt, buff, strlen(buff));
  	}
      else if (clt == data->p2)
  	{
  	  sprintf(buff, "FINISH %d\n", data->p1->fd_clt);
  	  write(data->p1->fd_clt, buff, strlen(buff));
  	}
    }
  data->nb_clt = data->nb_clt - 1;
  init_clt(data, clt);
}

int			get_client(t_data *data)
{
  struct sockaddr_in	s_in_clt;
  socklen_t		s_in_size;
  int			fd_clt;

  s_in_size = sizeof(s_in_clt);
  fd_clt = accept(data->fd_socket, (struct sockaddr *)&s_in_clt, &s_in_size);
  if (fd_clt == -1)
    {
      close(data->fd_socket);
      return (-1);
    }
  FD_SET(fd_clt, &data->read_set);
  if (fd_clt > data->max_fd)
    data->max_fd = fd_clt;
  data->nb_clt = data->nb_clt + 1;
  return (fd_clt);
}

int			make_socket(int port)
{
  int			sock_fd;
  struct protoent	*pe;
  struct sockaddr_in	srv_addr;

  if ((pe = getprotobyname("TCP")) == NULL)
    return (-1);
  sock_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (sock_fd == -1)
    return (-1);
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_addr.s_addr = INADDR_ANY;
  srv_addr.sin_port = htons(port);
  if ((bind(sock_fd, (const struct sockaddr *)&srv_addr,
	    sizeof(struct sockaddr_in))) == -1)
  {
    close(sock_fd);
    return (-1);
  }
  if (listen(sock_fd, 2) == -1)
    {
      close(sock_fd);
      return (-1);
    }
  return (sock_fd);
}
