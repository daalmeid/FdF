# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 16:48:15 by daalmeid          #+#    #+#              #
#    Updated: 2022/05/03 12:35:01 by daalmeid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################## Program #################

NAME = FdF

################## COLORS ##################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################## TERMINAL ################

RM		=		rm -f

################## COMPILER ################

CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra

################## FILES ###################

SRCS	=	srcs/fdf.c\
			srcs/ft_drawing.c\
			srcs/ft_line_creation_image.c\
			srcs/ft_base_grid.c\
			srcs/ft_final_design.c\
			srcs/fdf_utils.c\
			srcs/handler_clicks.c\
			srcs/handler_keys.c\
			srcs/measurements.c\
			srcs/pantry.c\
			srcs/instructions_square.c\
			srcs/rotations.c\
			srcs/zoom.c\

OBJS	=	$(SRCS:.c=.o)

LIB_DIR	=	-L./libft -L/usr/local/lib/
LIBS	=	-lft -lmlx
FRMWRKS	=	-framework OpenGL -framework AppKit

################## RULES ###################

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_DIR) $(LIBS) $(FRMWRKS)

libft:
	cd libft && make

################## CLEAN ###################

clean:
	cd libft && make clean
	$(RM) $(OBJS)

fclean: clean
	cd libft && make fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re