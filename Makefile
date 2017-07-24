##
## Makefile for jetpack2Tek3 in /home/arthur.clary/rendu/piscine_synthese/jetpack2Tek3_2016
## 
## Made by Clary Arthur
## Login   <arthur.clary@epitech.net>
## 
## Started on  Wed Jul 19 14:58:31 2017 Clary Arthur
## Last update Wed Jul 19 14:58:32 2017 Clary Arthur
##

SRV_SRC	=	server/
CLT_SRC =	client/

NAME1	=	serverJ2T3

NAME2	=	clientJ2T3

all:		server client

server:
		$(MAKE) -C $(SRV_SRC) all

client:
		$(MAKE) -C $(CLT_SRC) all

clean:
		$(MAKE) -C $(SRV_SRC) clean
		$(MAKE) -C $(CLT_SRC) clean

fclean:		clean
		$(MAKE) -C $(SRV_SRC) fclean
		$(MAKE) -C $(CLT_SRC) fclean
		rm -f $(NAME1) $(NAME2) 

re:		fclean all

.PHONY:		all server client clean fclean re
