##
## Makefile for lib in /home/arthur/Documents/B1-Système UNIX/PSU_2016_my_printf/
##
## Made by Arthur Chaloin
## Login   <arthur.chaloin@epitech.eu>
##
## Started on  Wed Nov  9 11:10:34 2016 Arthur Chaloin
## Last update Sat Dec 24 15:45:45 2016 Arthur Chaloin
##

CC	=	gcc

SRC	=	src/display/my_printf.c						\
		src/display/my_printf/flags/d_flag.c				\
		src/display/my_printf/flags/o_flag.c				\
		src/display/my_printf/flags/u_flag.c				\
		src/display/my_printf/flags/x_flag.c				\
		src/display/my_printf/flags/xx_flag.c				\
		src/display/my_printf/flags/b_flag.c				\
		src/display/my_printf/flags/s_flag.c				\
		src/display/my_printf/flags/ss_flag.c				\
		src/display/my_printf/flags/c_flag.c				\
		src/display/my_printf/flags/p_flag.c				\
		src/display/my_printf/flags/a_flag.c				\
		src/display/my_printf/flags/percent_flag.c			\
		src/display/my_printf/my_putchar.c				\
		src/display/my_printf/my_putstr.c				\
		src/display/my_printf/my_putnstr.c				\
		src/display/my_printf/my_showstr.c				\
		src/display/my_printf/my_shownstr.c				\
		src/display/my_printf/my_putnbr/my_putnbr.c			\
		src/display/my_printf/my_putnbr/my_putnbr_unsigned.c		\
		src/display/my_printf/my_putnbr/my_putnbr_long.c		\
		src/display/my_printf/my_putnbr/my_putnbr_long_unsigned.c	\
		src/display/my_printf/my_putnbr/my_putnbr_short.c		\
		src/display/my_printf/my_putnbr/my_putnbr_short_unsigned.c	\
		src/display/my_printf/utils.c					\
		src/display/my_printf/error.c					\
		src/string/my_strlen.c						\
		src/string/my_tablen.c						\
		src/string/my_strdup.c						\
		src/string/my_strcat.c						\
		src/string/my_tabdup.c						\
		src/string/my_str_contain.c					\
		src/tools/my_getnbr.c						\
		src/tools/my_strnbr.c						\
		src/tools/my_intlen.c						\
		src/tools/my_long_intlen.c					\
		src/tools/my_short_intlen.c					\
		src/parsing/map_file.c						\
		src/parsing/get_next_line.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra -g3

NAME	=	libmy.a

all:		$(NAME)

$(NAME):	$(OBJ)
		ar rc libmy.a $(OBJ)
		cp $(NAME) ../$(NAME)
		mkdir -p ../../include/
		cp include/my.h ../../include/my.h

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)
		rm -f ../$(NAME)
		rm -f ../../include/my.h

re:		fclean all

.PHONY:	all clean fclean re
