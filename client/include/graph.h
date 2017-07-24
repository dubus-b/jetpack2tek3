/*
** graph.h for Project-Master in /home/bdubus/jetpack2Tek3_2016/client/include
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Sat Jul 15 16:24:29 2017 Benjamin Dubus
** Last update Mon Jul 17 22:00:32 2017 Benjamin Dubus
*/

#ifndef GRAPH_H_
# define GRAPH_H_

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

typedef struct		s_jetpack
{
  sfText*		score;
  sfVector2f		backSize;
  sfRectangleShape*	elec;
  sfVideoMode		mode;
  sfRenderWindow*	win;
  sfVector2f		size;
  sfTexture*		space;
  sfTexture*		texP1;
  sfTexture*		texP2;
  sfTexture*		bitcoin;
  sfTexture*		metal;
  sfSprite*		player;
  sfSprite*		opponent;
  sfSprite*		coin;
  sfVector2f		elecSize;
  sfEvent		event;
  sfMusic*		starwars;
  sfRectangleShape*	back;
}			t_jetpack;


#endif /* !GRAPH_H_ */
