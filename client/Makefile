##
## Makefile for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
## 
## Made by Clary Arthur
## Login   <arthur.clary@epitech.net>
## 
## Started on  Tue Jul 18 18:17:46 2017 Clary Arthur
## Last update Tue Jul 18 18:17:47 2017 Clary Arthur
##

CC	=	gcc

RM	=	rm -f

CLT_SRC	=	srcs/

NAME	=	../clientJ2T3

SRC	=	$(CLT_SRC)main.c		\
		$(CLT_SRC)get_next_line.c	\
		$(CLT_SRC)tools.c		\
		$(CLT_SRC)initSfml.c		\
		$(CLT_SRC)print.c		\
		$(CLT_SRC)comCMD.c

OBJS	=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-pthread -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
CFLAGS	+=	-I./include 

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS)
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
