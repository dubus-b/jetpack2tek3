/*
** interpret.c for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016/server
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Fri Jul 14 14:53:36 2017 Clary Arthur
** Last update Tue Jul 18 16:00:47 2017 Clary Arthur
*/

# include "srv_jetpack.h"

int		cmp_sent(char *buff, char *wanted, int len)
{
  char		tmp[100];
  int		i;
  int		j;

  i = 0;
  while (buff[i] != '\0')
    {
      j = 0;
      memset(tmp, 0, 100);
      while (buff[i] != '\n' && buff[i] != '\0')
	{
	  tmp[j] = buff[i];
	  i = i + 1;
	  j = j + 1;
	}
      if (strncasecmp(tmp, wanted, len) == 0)
	return (0);
      i = i + 1;
    }
  return (1);
}

void		interpret(t_data *data, t_player *clt, t_Manag *Manag)
{
  char		buff[100];
  int		idx;

  memset(buff, 0, 100);
  if (read(clt->fd_clt, buff, 100) == 0)
    remove_clt(data, clt);
  idx = 0;
  while (idx < 5)
    {
      if (cmp_sent(buff, Manag[idx].fct, strlen(Manag[idx].fct)) == 0)
	Manag[idx].ptr(data, clt);
      idx = idx + 1;
    }
  if (data->p1->isREADY == 1 && data->p2->isREADY == 1 && g_GameRun == 0)
    {
      g_GameRun = 1;
      write(data->p1->fd_clt, "START\n", 6);
      write(data->p2->fd_clt, "START\n", 6);
    }
}

t_Manag		*init_Manag(t_Manag *Manag)
{
  if ((Manag = malloc(sizeof(t_Manag) * 5)) == NULL)
    exit(84);
  Manag[0].fct = "ID";
  Manag[0].ptr = _id;
  Manag[1].fct = "MAP";
  Manag[1].ptr = _map;
  Manag[2].fct = "READY";
  Manag[2].ptr = _ready;
  Manag[3].fct = "FIRE 1";
  Manag[3].ptr = _activ_fire;
  Manag[4].fct = "FIRE 0";
  Manag[4].ptr = _desactiv_fire;
  return (Manag);
}
