/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:49:09 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/14 16:51:13 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

int	cross_handler(void *param)
{
	t_cd	**grid;
	void	**new;

	new = (void **) param;
	grid = keep_grid(NULL);
	ptr_ptr_free((void **) grid);
	mlx_destroy_image(new[0], new[2]);
	exit(0);
}

void	z_altered_image_put(t_cd **grid, void *param)
{
	void	**new;
	t_cd	xy_image;
	int		width;
	int		height;

	new = (void **) param;
	width = image_width(grid_based_size(grid), grid);
	height = image_height(grid_based_size(grid), grid);
	xy_image = keep_xy_image(-2147483648, -2147483648);
	mlx_destroy_image(new[0], new[2]);
	new[2] = mlx_new_image(new[0], width + 6, height + 6);
	ft_drawing(grid, new);
	mlx_put_image_to_window(new[0], new[1], new[2], xy_image.x, xy_image.y);
}

int	click_handler(int button, int x, int y, void *param)
{
	t_cd	**grid;
	int		z_sign;

	grid = keep_grid(NULL);
	y = 0;
	z_sign = -1;
	if (button == 4)
		z_sign = 1;
	if (button == 5 || button == 4)
	{
		while (grid[y] != NULL)
		{
			x = 0;
			while (grid[y][x].x != -2147483648)
			{
				if (grid[y][x].z > 0)
					grid[y][x].y += grid[y][x].z * z_sign;
				else if (grid[y][x].z < 0)
					grid[y][x].y -= grid[y][x].z * z_sign;
				x++;
			}
			y++;
		}
	}
	z_altered_image_put(grid, param);
	return (0);
}

void	copy_z(t_cd **old_grid, t_cd **new_grid)
{
	int	i;
	int	j;

	i = 0;
	while (old_grid[i] != NULL)
	{
		j = 0;
		while (old_grid[i][j].x != -2147483648)
		{
			new_grid[i][j].z = old_grid[i][j].z;
			new_grid[i][j].color = old_grid[i][j].color;
			new_grid[i][j].y -= new_grid[i][j].z;
			j++;
		}
		i++;
	}
}

void	zoom_handler(void **ptr, int zoom)
{
	int		width;
	int		height;
	t_cd	size;
	t_cd	**grid;

	size = grid_based_size(keep_grid(NULL));
	grid = ft_prep_base_grid(size, zoom);
	copy_z(keep_grid(NULL), grid);
	ptr_ptr_free((void **) keep_grid(NULL));
	keep_grid(grid);
	width = image_width(size, grid) + 6;
	height = image_height(size, grid) + 6;
	mlx_destroy_image(ptr[0], ptr[2]);
	ptr[2] = mlx_new_image(ptr[0], width, height);
	ft_drawing(grid, ptr);
}

int	key_handler(int key, void *param)
{
	void		**ptr;
	static int	x = 50;
	static int	y = 50;

	ptr = param;
	if (key == 53)
	{	
		ptr_ptr_free((void **) keep_grid(NULL));
		mlx_destroy_image(ptr[0], ptr[2]);
		exit(0);
	}
	else if (key == 123)
		mlx_put_image_to_window(ptr[0], ptr[1], ptr[2], x -= 2, y);
	else if (key == 124)
		mlx_put_image_to_window(ptr[0], ptr[1], ptr[2], x += 2, y);
	else if (key == 125)
		mlx_put_image_to_window(ptr[0], ptr[1], ptr[2], x, y += 2);
	else if (key == 126)
		mlx_put_image_to_window(ptr[0], ptr[1], ptr[2], x, y -= 2);
	keep_xy_image(x, y);
	if (key == 69 || key == 24)
	{
		zoom_handler(ptr, 1);
		mlx_put_image_to_window(ptr[0], ptr[1], ptr[2], x, y);
	}
	else if (key == 78 || key == 27)
	{
		zoom_handler(ptr, -1);
		mlx_put_image_to_window(ptr[0], ptr[1], ptr[2], x, y);
	}
	return (0);
}
