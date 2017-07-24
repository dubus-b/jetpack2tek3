/*
** initSfml.c for Project-Master in /home/bdubus/jetpack2Tek3_2016/client/srcs
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Sat Jul 15 16:27:34 2017 Benjamin Dubus
** Last update Wed Jul 19 14:26:19 2017 Benjamin Dubus
*/

#include "client.h"
#include "graph.h"

static	sfText*			setText()
{
  sfText* tx;
  
  tx = sfText_create();
  sfText_setFont(tx, sfFont_createFromFile("client/asset/Starjedi.ttf"));
  sfText_setCharacterSize(tx, 40);
  sfText_setColor(tx, sfYellow);;
  return (tx);
}

static	sfVector2f		makeSize(int nbr, int y)
{
  sfVector2f	size;
  size.x = nbr;
  size.y = y;
  return (size);
}

static	sfVector2f		makeScale(double nbr)
{
  sfVector2f	sc;

  sc.x = nbr;
  sc.y = nbr;
  return (sc);
}


static sfSprite*	makeSprite(sfTexture* tex, double scale, int color)
{
  sfSprite*	sp;
  sp = sfSprite_create();
  sfSprite_setTexture(sp, tex, sfTrue);
  sfSprite_setScale(sp, makeScale(scale));
  if (color == 1)
    sfSprite_setColor(sp, sfRed);
  return (sp);
}

void		free_sfml(t_jetpack *free)
{
  sfMusic_destroy(free->starwars);
  sfSprite_destroy(free->player);
  sfSprite_destroy(free->opponent);
  sfSprite_destroy(free->coin);
  sfRenderWindow_destroy(free->win);
}


void		initRsc(t_jetpack *init, int width, int height)
{  
  init->mode.width = (width * 20);
  init->mode.height = (height * 20) + 100;
  init->mode.bitsPerPixel = 32;
  init->elecSize = makeSize(20, 20);
  init->backSize = makeSize(init->mode.width, init->mode.height - 100);
  init->space = sfTexture_createFromFile("client/asset/space.jpg", NULL);
  init->bitcoin = sfTexture_createFromFile("client/asset/death.png", NULL);
  init->metal = sfTexture_createFromFile("client/asset/elec.jpg", NULL);
  init->texP1 = sfTexture_createFromFile("client/asset/x-wing.png", NULL);
  init->starwars = sfMusic_createFromFile("client/asset/starwars.ogg");
  init->elec = sfRectangleShape_create();
  init->back = sfRectangleShape_create();
  sfRectangleShape_setSize(init->elec, init->elecSize);
  sfRectangleShape_setSize(init->back, init->backSize);
  sfRectangleShape_setTexture(init->back, init->space, sfTrue);
  sfRectangleShape_setTexture(init->elec, init->metal, sfTrue);
  init->player = makeSprite(init->texP1, 0.18, 0);
  init->opponent = makeSprite(init->texP1,0.18, 1);
  init->coin = makeSprite(init->bitcoin, 0.667, 0);
  init->score = setText();
  init->win = sfRenderWindow_create(init->mode, "jetpack2tek3 Star Wars Edition"
				    , sfResize | sfClose, NULL);
  sfRenderWindow_clear(init->win, sfBlack);
  sfRenderWindow_drawRectangleShape(init->win, init->back, NULL);
  sfRenderWindow_display(init->win);
}
