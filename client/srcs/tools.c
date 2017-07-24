/*
** tools.c for Project-Master in /home/bdubus/jetpack2Tek3_2016/client/srcs
** 
** Made by Benjamin Dubus
** Login   <benjamin.dubus@epitech.eu>
** 
** Started on  Sat Jul 15 15:58:44 2017 Benjamin Dubus
** Last update Sat Jul 15 16:05:48 2017 Benjamin Dubus
*/

#include "client.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void    my_put_nbr(int nbr)
{
  if (nbr == -2147483648)
    {
      puts("-2147483648");
      return ;
    }
  if (nbr < 0)
    {
      my_putchar('-');
      nbr = nbr * -1;
    }
  if (nbr >= 10)
    {
      my_put_nbr(nbr / 10);
      my_putchar(nbr % 10 + '0');
    }
  else
    my_putchar(nbr + '0');
}

static void    *malloc_size(size_t size)
{
  void  *tmp;

  tmp = malloc(size);
  if (!tmp)
    exit(1);
  return (tmp);
}

static int		countWord(const char *str)
{
  int	idx;
  int	word;

  word = 1;
  idx = 0;
  while (str[idx])
    {
      if (str[idx] != ' ')
	word++;
      idx++;
    }
  return (word);
}

char    **response_to_wordtab(char *str, char delim)
{
  char  **tab;
  int   i;
  char  *tmp;
  char  d[2];

  d[0] = delim;
  d[1] = 0;
  tab = malloc_size(sizeof(char *) * (countWord(str) + 2));
  i = 0;
  while ((tmp = strtok(i == 0 ? str : NULL, d)))
    {
      tab[i] = tmp;
      i++;
    }
  tab[i] = 0;
  return (tab);
}
