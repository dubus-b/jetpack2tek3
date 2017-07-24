/*
** srv_jetpack.h for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
** 
** Made by Clary Arthur
** Login   <arthur.clary@epitech.net>
** 
** Started on  Thu Jul 13 14:49:28 2017 Clary Arthur
** Last update Tue Jul 18 15:52:57 2017 Clary Arthur
*/

#ifndef SRV_JETPACK_H_
# define SRV_JETPACK_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <string.h>
# include <signal.h>

typedef struct	s_player
{
  int		fd_clt;
  int		score;
  int		haveID;
  int		haveMAP;
  int		isREADY;
  int		isFIRE;
  double	y;
}		t_player;

typedef struct	s_data
{
  int		_port;
  int		_gravity;
  char		*_map;
  fd_set	read_set;
  fd_set	write_set;
  int		fd_socket;
  t_player	*p1;
  t_player	*p2;
  int		max_fd;
  int		nb_clt;
  //  int		GameRun;//
  char		**savMap;
  char		**Map;
  double	length_map;
  double	height_map;
  double	x;
}		t_data;

typedef struct	s_Manag
{
  char		*fct;
  void		(*ptr)(t_data *data, t_player *clt);
}		t_Manag;

int		g_GameRun;

void		end_game(t_data *data, int flag_why);
void		search_strike(t_data *data, t_player *clt);
void		send_status(t_data *data);
void		calc_y(t_data *data, t_player *clt);
void		play_game(t_data *data);
int		cmp_sent(char *buff, char *wanted, int len);
void		interpret(t_data *data, t_player *clt, t_Manag *Manag);
void		reset_fd(t_data *data);
void		check_fd(t_data *data, t_Manag *Manag);
void		run_game(t_data *data);
void		remove_clt(t_data *data, t_player *clt);
int		get_client(t_data *data);
int		make_socket(int port);
void		_id(t_data *data, t_player *clt);
void		_map(t_data *data, t_player *clt);
void		_ready(t_data *data, t_player *clt);
void		_activ_fire(t_data *data, t_player *clt);
void		_desactiv_fire(t_data *data, t_player *clt);
t_Manag		*init_Manag(t_Manag *Manag);
void		valid_map(char *map);
void		eject_endline(t_data *data, char *map, int len, int wid);
void		recup_tab_map(t_data *data, char *map, int kdx);
int		check_map(t_data *data, char *file);
int		get_map(t_data *data, char *file);
void		alloc_map(t_data *data);
void		init_clt(t_data *data, t_player *clt);
void		init_game(t_data *data);
void		*xmalloc(size_t size);
char		*my__strcat(char *str, char buff);
int		finalise(char **unsent, char *buff, int i, int rc);
char		*get_unsent(char **unsent, int *ret);
char		*get_next_line(int fd);
void		get_sigint(int signal);
int		get_arg(t_data *data, int ac, char **av, int isFind);
void		exit_error(char *arg);
void		free_all(t_data *data, t_Manag *Manag);
void		close_all(t_data *data);

#endif
