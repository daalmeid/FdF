/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:53:15 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/14 16:59:07 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct s_cd
{
	int	x;
	int	y;
	int z;
	int	color;
}	t_cd;
int		ft_line_creation(int x, int y, unsigned int color, void *param);
void	ft_drawing(t_cd **grid, void **new);
t_cd	**ft_prep_base_grid(t_cd size, int zoom);
t_cd	**ft_final_design(t_cd **grid, char *map);
int		file_dealer(int fd, char *map);
void	ptr_ptr_free(void **ptr);
int		key_handler(int key, void *param);
int		file_dealer(int fd, char *map);
void	ptr_ptr_free(void **ptr);

typedef struct	s_data 
{
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_data;
t_data	handle_new_image(void **new);
void	my_pixel_put(t_data *data, int x, int y, int color);
t_cd	**keep_grid(t_cd **grid);
t_cd	keep_xy_image(int x, int y);
int	cross_handler(void *param);
int	click_handler(int button, int x, int y, void *param);
t_cd	grid_based_size(t_cd **grid);
int	image_height(t_cd size, t_cd **grid);
int	image_width(t_cd size, t_cd **grid);

#endif