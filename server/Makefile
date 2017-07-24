##
## Makefile for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
## 
## Made by Clary Arthur
## Login   <arthur.clary@epitech.net>
## 
## Started on  Tue Jul 18 18:17:24 2017 Clary Arthur
## Last update Wed Jul 19 16:47:22 2017 Clary Arthur
##

CC	=	gcc

RM	=	rm -f

SRV_SRC	=	srcs/

NAME	=	../serverJ2T3

SRC	=	$(SRV_SRC)game.c \
		$(SRV_SRC)utility.c \
		$(SRV_SRC)get_next_line.c \
		$(SRV_SRC)init.c \
		$(SRV_SRC)interpret.c \
		$(SRV_SRC)commands.c \
		$(SRV_SRC)find_map.c \
		$(SRV_SRC)socket.c \
		$(SRV_SRC)main.c

OBJS	=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Werror -Wextra
CFLAGS	+=	-I./include -g3

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

server:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
