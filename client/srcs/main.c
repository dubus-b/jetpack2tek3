/*
** client_.c for Project-Master in /home/bdubus/jetpack2Tek3_2016/client
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Thu Jul 13 15:17:56 2017 Benjamin Dubus
** Last update Wed Jul 19 15:47:03 2017 Benjamin Dubus
*/

#include "client.h"
#include "graph.h"


void			*gui(void *_info)
{
  t_netTools		*info;
  t_jetpack		game;
  info = (t_netTools*)_info;
  int			init;

  init = 0;
  while (info->finish == 0)
    {
      if (info->startGUI == 0 && init == 0)
	{
	  init = 1;
	  initRsc(&game, info->width, info->height);
	}
      if (info->startGUI == 0 && init == 1 && info->start == 0)
	{
	  while (sfRenderWindow_pollEvent(game.win, &game.event))
	    {
	      if (game.event.type == sfEvtClosed)
		{
		  sfRenderWindow_close(game.win);
		  info->finish = -2;
		  free_sfml(&game);
		  pthread_exit(NULL);
		}
	      if (game.event.type == sfEvtKeyPressed)
		info->fire = 1;
	      else
		info->fire = 0;
	    }
	  if (sfMusic_getStatus(game.starwars) == sfStopped)
	    sfMusic_play(game.starwars);
	  sfRenderWindow_clear(game.win, sfBlack);
	  printMap(&game, info);
	  printPlayers(&game, info);
	  printScore(&game, info);
	  sfRenderWindow_display(game.win);
	}
    }
  sfRenderWindow_close(game.win);
  free_sfml(&game);
  pthread_exit(NULL);
}

char			**send_receive(int soc, char *str, int fire)
{
  char	**split;
  
  if (fire == -1)
    dprintf(soc,"%s\n", str);
  else if (fire >= 0)
    dprintf(soc,"FIRE %d\n", fire);
  split = response_to_wordtab(get_next_line(soc), ' ');
  return (split);
}

static void		*listen_srv(void *_net)
{
  t_netTools		*net;
  char			**split;

  net = (t_netTools*)_net;
  while (net->finish == 0)
    {
      if (net->startGUI != 0)
	{
	  split = send_receive(net->socket_id, "ID", -1);
	  if (strcmp(split[0], "ID") == 0)
	    net->id = atoi(split[1]);
	  split = send_receive(net->socket_id, "MAP", -1);
	  if (strcmp(split[0], "MAP") == 0)
	    getMap(split, net);
	  net->startGUI = 0;
	  write(net->socket_id,"READY\n", strlen("READY\n"));
	}
      if (net->startGUI != 1)
	{
	  if (net->start != 0)
	    {
	      split = send_receive(net->socket_id, "START", -2);
	      if (strcmp(split[0], "START") == 0)
		net->start = 0;
	    }
	  else
	    {
	      split = send_receive(net->socket_id, "FIRE", net->fire);
	      if (strcmp(split[0], "PLAYER") == 0)
		getPlayer(split, net);
	      if (strcmp(split[0], "COIN") == 0)
		getCoin(split, net);
	      if (strcmp(split[0], "FINISH") == 0)
		{
		  net->finish = atoi(split[1]);
		  close(net->socket_id);
		  pthread_exit(NULL);
		}
	    }
	}
    }
  pthread_exit(NULL);
}

static void		analyseArg(t_netTools *net, int argc, char **argv, char *opt)
{
  int			c;
  
  if (argc < 5)
    exit(0);
  net->startGUI = 1;
  while ((c = getopt(argc, argv, opt)) != EOF)
    {
      if (c == 'h')
	net->ipAddress = optarg;
      else if (c == 'p')
	net->port = atoi(optarg);
      else
	exit(1);
    }
  if (strcmp(net->ipAddress, "localhost") == 0)
    net->ipAddress = strdup("127.0.0.1");
  if (strcmp(net->ipAddress, "epitrade.fr") == 0)
    net->ipAddress = strdup("93.21.68.137");
}

static t_netTools	initNetworking(int argc, char **argv)
{
  int			valid;
  t_netTools		ret;

  ret.start = 1;
  ret.finish = 0;
  analyseArg(&ret, argc, argv, "h:p:");
  ret.socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if (ret.socket_id == -1)
    {
      printf("Error socket\n");
      exit(1);
    }
  ret.sai.sin_family = AF_INET;
  ret.sai.sin_addr.s_addr = inet_addr(ret.ipAddress);
  ret.sai.sin_port = htons(ret.port);
  valid = connect(ret.socket_id, (struct sockaddr *)&ret.sai, sizeof(struct sockaddr_in));
  if (valid != -1)
    printf("Connected to %s: %d\n", ret.ipAddress,ret.port);
  else
    {
      printf("Connection error\n");
      exit (1);
    }
  return (ret);
}

int		main(int argc, char **argv)
{
  t_netTools	network;
  pthread_t	graphic;
  pthread_t	com;
  
  network = initNetworking(argc, argv);
  pthread_create(&com, NULL, listen_srv, &network);
  pthread_create(&graphic, NULL, gui, &network);
  pthread_join(com, NULL);
  pthread_join(graphic, NULL);
  if (network.finish == -2)
    printf("You left the game\n");
  else if (network.finish == network.id)
    printf("You win !\n");
  else if (network.finish == -1)
    printf("Nobody win !\n");
  else
    printf("You lose !\n");
  return(0);
}
