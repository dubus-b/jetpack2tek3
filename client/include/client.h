/*
** client.h for Project-Master in /home/bdubus/jetpack2Tek3_2016/client
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Thu Jul 13 14:36:41 2017 Benjamin Dubus
** Last update Wed Jul 19 15:26:05 2017 Clary Arthur
*/

#ifndef CLIENT_H_
# define CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <pthread.h>
#include "graph.h"

typedef struct	s_netTools
{
  char			*ipAddress;
  int			port;
  int			socket_id;
  struct sockaddr_in	sai;  
  char			**map;
  int			height;
  int			width;
  int			id;
  int			fire;
  int			score;
  int			hisScore;
  double		p1x;
  double		p1y;
  double		p2x;
  double		p2y;
  int			finish;
  int			start;
  int			startGUI;
  
}		t_netTools;

void			printScore(t_jetpack *jet, t_netTools *net);
void			printPlayers(t_jetpack *jet, t_netTools *net);
void			printMap(t_jetpack *jet, t_netTools *net);
void			getPlayer(char **split, t_netTools *net);
void			getCoin(char **split, t_netTools *net);
void			getMap(char **split, t_netTools *net);
char			*get_next_line(int fd);
void			my_putchar(char c);
void			my_put_nbr(int nbr);
char			**response_to_wordtab(char *str, char delim);
void			initRsc(t_jetpack *init, int width, int height);
void			free_sfml(t_jetpack *free);

#endif /* !CLIENT_H_ */




/* typedef struct	s_gameData */
/* { */
/*   char	**map; */
/*   int	height; */
/*   int	width; */
/*   int	id; */
/*   int	fire; */
/*   int	score; */
/*   int	x; */
/*   int	y; */
/* }		t_gameData; */

