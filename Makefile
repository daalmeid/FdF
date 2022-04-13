# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 15:18:15 by daalmeid          #+#    #+#              #
#    Updated: 2022/04/13 19:04:01 by daalmeid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= FdF

SRCS	= fdf.c ft_drawing.c ft_line_creation_image.c ft_base_grid.c\
		  ft_final_design.c fdf_utils.c handler_clicks.c handler_keys.c\
		  measurements.c pantry.c instructions_square.c rotations.c zoom.c

OBJS	= *.o

RM		= rm -f

LIBFT	= libft.a

$(NAME): $(LIBFT) $(OBJS)
	gcc -Wall -Wextra -Werror -I /usr/local/include $(SRCS) -L /usr/local/lib/\
	-lmlx -L ./libft -lft -framework OpenGL -framework AppKit -o $(NAME)

$(OBJS):
	gcc -Wall -Wextra -Werror -c $(SRCS)

$(LIBFT):
	cd libft/ && make && cp libft.h ../
	
all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

bonus: 
