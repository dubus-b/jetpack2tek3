/*
** comCMD.c for Project-Master in /home/bdubus/jetpack2Tek3_2016/client/srcs
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Tue Jul 18 11:02:35 2017 Benjamin Dubus
** Last update Tue Jul 18 11:05:13 2017 Benjamin Dubus
*/

#include "client.h"

void			getPlayer(char **split, t_netTools *net)
{
  if (atoi(split[1]) == net->id)
    {
      net->p1x = atof(split[2]);
      net->p1y = atof(split[3]);
      net->p1y = (net->height - net->p1y) - 1;
      net->score = atoi(split[4]);
    }
  else
    {
      net->p2x = atof(split[2]);
      net->p2y = atof(split[3]);
      net->p2y = (net->height - net->p2y) - 1;
      net->hisScore = atoi(split[4]);
    }
}

void			getCoin(char **split, t_netTools *net)
{
  int			x;
  int			y;

  x = atoi(split[2]);
  y = atoi(split[3]);
  if(net->map[(net->height - 1) - y][x] == 'c')
    net->map[(net->height - 1) - y][x] = '_';
}

void				getMap(char **split, t_netTools *net)
{
  int				idx;
  int				parc;
  int				tmp;
  
  tmp = 0;
  idx = 0;
  net->width = atoi(split[1]);
  net->height = atoi(split[2]);
  net->map = malloc(sizeof(char *) * (net->height + 1));
  while (idx != net->height)
    {
      net->map[idx] = malloc(sizeof(char) * (net->width + 1));
      idx++;
    }
  idx = 0;
  while (idx != net->height)
    {
      parc = 0;
      while (parc != net->width)
	{
	  
	  net->map[idx][parc] = split[3][tmp];
	  tmp++;
	  parc++;
	}
      idx++;
    }
}
