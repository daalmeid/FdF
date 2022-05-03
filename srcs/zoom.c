/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:03:18 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 12:34:30 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"
#include "../headers/libft.h"
#include <stdio.h>

void	copy_z(t_cd **old_grid, t_cd **new_grid)
{
	int	i;
	int	j;
	int	z_change;

	i = 0;
	z_change = keep_z_change(-2147483648);
	while (old_grid[i] != NULL)
	{
		j = 0;
		while (old_grid[i][j].x != -2147483648)
		{
			new_grid[i][j].z = old_grid[i][j].z;
			new_grid[i][j].color = old_grid[i][j].color;
			new_grid[i][j].y -= new_grid[i][j].z * z_change;
			j++;
		}
		i++;
	}
}

void	zoom_handler_error(t_cd **grid)
{
	perror("Error creating image");
	ptr_ptr_free((void **)grid);
	exit(0);
}

void	zoom_handler(void **mlx, int zoom, int *x, int *y)
{
	int		width;
	int		height;
	t_cd	size;
	t_cd	**grid;
	t_cd	**old_grid;

	old_grid = keep_grid(NULL);
	size = grid_based_size(old_grid);
	if (ft_prep_base_grid(size, zoom, &grid) == NULL)
	{
		ptr_ptr_free((void **)old_grid);
		exit(0);
	}
	copy_z(old_grid, grid);
	width = image_width(size, grid) + 6;
	height = image_height(size, grid) + 6;
	*x -= (width - (image_width(size, old_grid) + 6)) / 2;
	*y -= (height - (image_height(size, old_grid) + 6)) / 2;
	ptr_ptr_free((void **) old_grid);
	keep_grid(grid);
	mlx_destroy_image(mlx[0], mlx[2]);
	mlx[2] = mlx_new_image(mlx[0], width, height);
	if (!mlx[2])
		zoom_handler_error(grid);
	ft_drawing(grid, mlx);
}
