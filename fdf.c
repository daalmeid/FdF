/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:41:20 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/14 16:56:54 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

t_cd	base_grid_dimensions(char *map, int fd)
{
	char	*line;
	char	**x_axis;
	t_cd	size;

	size.x = 0;
	size.y = 0;
	fd = file_dealer(fd, map);
	line = get_next_line(fd);
	x_axis = ft_split(line, ' ');
	if (!x_axis)
	{
		write(2, "Error getting dimensions\n", 26);
		exit(0);
	}
	while (x_axis[size.x] != NULL && ft_strncmp(x_axis[size.x], "\n", 2))
		size.x++;
	ptr_ptr_free((void **) x_axis);
	while (line != NULL)
	{		
		size.y++;
		free(line);
		line = get_next_line(fd);
	}
	fd = file_dealer(fd, map);
	return (size);
}

int	image_width(t_cd size, t_cd **grid)
{
	int	width_low;
	int	width_high;

	width_low = grid[size.y - 1][0].x;
	width_high = grid[0][size.x - 1].x;
	return (width_high - width_low + 1);
}

void	correct_y(t_cd **grid, t_cd size, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			grid[i][j].y -= (y - 3);
			j++;
		}
		i++;
	}
}

int	image_height(t_cd size, t_cd **grid)
{
	int	height_low;
	int	height_high;
	int	i;
	int	j;

	i = 0;
	height_low = grid[0][0].y;
	height_high = grid[size.y - 1][size.x - 1].y;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (grid[i][j].y < height_low)
				height_low = grid[i][j].y;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (grid[i][j].y > height_high)
				height_high = grid[i][j].y;
			j++;
		}
		i++;
	}
	correct_y(grid, size, height_low);
	return (height_high - height_low + 1);
}

t_cd	**keep_grid(t_cd **grid)
{
	static t_cd	**save;

	if (grid != NULL)
	{
		save = grid;
		return (0);
	}
	return (save);
}

t_cd	grid_based_size(t_cd **grid)
{
	t_cd	size;

	size.x = 0;
	size.y = 0;
	while (grid[size.y][size.x].x != -2147483648)
		size.x++;
	while (grid[size.y] != NULL)
		size.y++;
	return (size);
}

void	hooks(void **new)
{
	mlx_key_hook(new[1], key_handler, new);
	mlx_hook(new[1], 17, 0, cross_handler, new);
	mlx_mouse_hook(new[1], click_handler, new);
}

int	main(int ac, char **av)
{
	void	*new[3];
	t_cd	**grid;
	t_cd	size;
	int		width;
	int		height;

	if (ac != 2)
		return (0);
	size = base_grid_dimensions(av[1], -2);
	grid = ft_prep_base_grid(size, 0);
	if (grid == NULL || ft_final_design(grid, av[1]) == NULL)
	{
		write(2, "Error creating grid.\n", 22);
		return (0);
	}
	keep_grid(grid);
	width = image_width(size, grid);
	height = image_height(size, grid);
	new[0] = mlx_init();
	new[1] = mlx_new_window(new[0], width + 100, height + 100, "FdF");
	new[2] = mlx_new_image(new[0], width + 6, height + 6);
	hooks(new);
	ft_drawing(grid, new);
	keep_xy_image(50, 50);
	mlx_put_image_to_window(new[0], new[1], new[2], 50, 50);
	mlx_loop(new[0]);
	return (0);
}
