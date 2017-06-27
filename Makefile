##
## Makefile for do-op in /home/arthur/Documents/Piscine/CPool_Day10/do-op/
##
## Made by Arthur Chaloin
## Login   <arthur.chaloin@epitech.eu>
##
## Started on  Fri Oct 14 19:00:42 2016 Arthur Chaloin
## Last update Sat Mar 18 15:46:47 2017 Arthur Chaloin
## Last update Fri Oct 28 15:38:03 2016 Arthur Chaloin
##

CC		= gcc

RM		= rm -f

CFLAGS		= -W -Wall -Wextra -Iinclude/ -Ofast

NAME		= wolf3d

LIB		= -Llib/my/ -lmy -lm -lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system -lsfml-graphics -lcsfml-audio -lsfml-window -lsfml-system

SRC		= src/wolf3d.c			\
		  src/game/game.c		\
		  src/game/raycast.c		\
		  src/game/move.c		\
		  src/game/minimap.c		\
		  src/game/utils.c		\
		  src/game/pnj.c		\
		  src/game/pnj_core.c		\
		  src/game/dead.c		\
		  src/event/events.c		\
		  src/event/keys.c		\
		  src/struct/menu.c		\
		  src/struct/load_map.c		\
		  src/struct/list_map.c		\
		  src/struct/get_map.c		\
		  src/struct/save.c		\
		  src/editor/editor.c		\
		  src/editor/editor_display.c	\
		  src/editor/new.c		\
		  src/video/draw.c		\
		  src/video/blit.c		\
		  src/video/put_pixel.c		\
		  src/video/video.c		\
		  src/video/display/display.c	\
		  src/video/display/weapon.c	\
		  src/video/display/view.c	\
		  src/video/display/entity.c

OBJ		= obj/wolf3d.o			\
		  obj/game/game.o		\
		  obj/game/raycast.o		\
		  obj/game/move.o		\
		  obj/game/minimap.o		\
		  obj/game/utils.o		\
		  obj/game/pnj.o		\
		  obj/game/pnj_core.o		\
		  obj/game/dead.o		\
		  obj/event/events.o		\
		  obj/event/keys.o		\
		  obj/struct/menu.o		\
		  obj/struct/load_map.o		\
		  obj/struct/list_map.o		\
		  obj/struct/get_map.o		\
		  obj/struct/save.o		\
		  obj/editor/editor.o		\
		  obj/editor/editor_display.o	\
		  obj/editor/new.o		\
		  obj/video/draw.o		\
		  obj/video/blit.o		\
		  obj/video/put_pixel.o		\
		  obj/video/video.o		\
		  obj/video/display/display.o	\
		  obj/video/display/weapon.o	\
		  obj/video/display/view.o	\
		  obj/video/display/entity.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIB) $(CFLAGS)

obj/%.o: src/%.c
	@mkdir -p obj/
	@mkdir -p obj/game/
	@mkdir -p obj/video/
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

lib:
	cd lib/my && make re && make clean

re : fclean all

.PHONY : all clean fclean lib re
