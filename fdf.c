/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:41:20 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 17:10:21 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

static t_cd	base_grid_dimensions(char *map, int fd, t_cd *size)
{
	char	*line;
	char	**x_axis;

	size->x = 0;
	size->y = 0;
	fd = file_dealer(fd, map);
	line = get_next_line(fd);
	x_axis = ft_split(line, ' ');
	if (!x_axis)
	{
		file_dealer(fd, map);
		perror("Error splitting first line/file empty");
		exit(0);
	}
	while (x_axis[size->x] != NULL && ft_strncmp(x_axis[size->x], "\n", 2))
		size->x++;
	ptr_ptr_free((void **) x_axis);
	while (line != NULL)
	{		
		size->y++;
		free(line);
		line = get_next_line(fd);
	}
	fd = file_dealer(fd, map);
	return (*size);
}

static void	hooks(void **mlx)
{
	mlx_key_hook(mlx[1], key_handler, mlx);
	mlx_hook(mlx[1], 17, 0, cross_handler, mlx);
	mlx_mouse_hook(mlx[1], click_handler, mlx);
}

static void	prep_mlx_pointers(void *mlx[3], t_cd **grid, int width, int height)
{
	mlx[0] = mlx_init();
	if (!mlx[0])
	{
		perror("Error establishing connection to graphical system");
		ptr_ptr_free((void **)grid);
		exit(0);
	}
	if (width <= 2000 && height <= 1000)
		mlx[1] = mlx_new_window(mlx[0], width + 100, height + 100, "FdF");
	else
		mlx[1] = mlx_new_window(mlx[0], 2500, 1500, "FdF");
	if (!mlx[1])
	{
		perror("Error creating window");
		ptr_ptr_free((void **)grid);
		exit(0);
	}
	mlx[2] = mlx_new_image(mlx[0], width + 6, height + 6);
	if (!mlx[2])
	{
		perror("Error creating image");
		ptr_ptr_free((void **)grid);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	void	*mlx[3];
	t_cd	**grid;
	t_cd	size;
	int		width;
	int		height;

	if (ac != 2)
	{
		ft_putendl_fd("Wrong input. Correct format: ./FdF <FILE>.fdf", 2);
		return (0);
	}
	size = base_grid_dimensions(av[1], -2, &size);
	ft_prep_base_grid(size, 0, &grid);
	if (grid == NULL || ft_final_design(grid, av[1]) == NULL)
		return (0);
	width = image_width(size, grid);
	height = image_height(size, grid);
	prep_mlx_pointers(mlx, grid, width, height);
	hooks(mlx);
	ft_drawing(grid, mlx);
	keep_xy_image(50, 50);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 50, 50);
	put_instructions(mlx, 50, 50, 0);
	mlx_loop(mlx[0]);
	return (0);
}
