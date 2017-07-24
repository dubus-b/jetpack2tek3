/*
** print.c for Project-Master in /home/bdubus/jetpack2Tek3_2016/client/srcs
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Tue Jul 18 11:05:44 2017 Benjamin Dubus
** Last update Tue Jul 18 11:12:14 2017 Benjamin Dubus
*/

#include "graph.h"
#include "client.h"

void			printScore(t_jetpack *jet, t_netTools *net)
{
  sfVector2f		pos;
  char*			tmp;

  tmp = malloc(sizeof(char) * 50);
  sprintf(tmp,"Force:%d dark side: %d", net->score, net->hisScore);
  sfText_setString(jet->score, tmp);
  pos.x = 0;
  pos.y = net->height * jet->elecSize.y;
  sfText_setPosition(jet->score, pos);
  sfRenderWindow_drawText(jet->win, jet->score, NULL);
  free(tmp);
}

void			printPlayers(t_jetpack *jet, t_netTools *net)
{
  sfVector2f		myPos;
  sfVector2f		hisPos;

  myPos.x = net->p1x * jet->elecSize.x;
  myPos.y = net->p1y * jet->elecSize.y;
  hisPos.x = net->p2x * jet->elecSize.x;
  hisPos.y = net->p2y * jet->elecSize.y;
  sfSprite_setPosition(jet->player, myPos);
  sfSprite_setPosition(jet->opponent, hisPos);
  sfRenderWindow_drawSprite(jet->win, jet->opponent, NULL);
  sfRenderWindow_drawSprite(jet->win, jet->player, NULL);
}

void			printMap(t_jetpack *jet, t_netTools *net)
{
  int			idx;
  int			idxY;
  sfVector2f		pos;

  idx = 0;
  idxY = 0;
  pos.x = idx;
  pos.y = idxY;  
  sfRenderWindow_drawRectangleShape(jet->win, jet->back, NULL);
  while (idxY != net->height)
    {
      idx = 0;
      pos.x = idx * jet->elecSize.x;
      while (idx != net->width)
	{
	  if (net->map[idxY][idx] == 'c')
	    sfRenderWindow_drawSprite(jet->win, jet->coin, NULL);
	  else if (net->map[idxY][idx] == 'e')
	    sfRenderWindow_drawRectangleShape(jet->win, jet->elec, NULL);
	  sfSprite_setPosition(jet->coin, pos);
	  sfRectangleShape_setPosition(jet->elec, pos);
	  idx++;
	  pos.x = idx * jet->elecSize.x;
	}
      idxY++;
      pos.y = idxY * jet->elecSize.y;
    }
}
