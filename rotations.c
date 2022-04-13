/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:36:05 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 16:51:08 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

static void	rotation_right(t_cd **old_grid, t_cd **new_grid)
{
	int		i;
	int		j;
	t_cd	size;

	i = 0;
	size = grid_based_size(old_grid);
	size.y--;
	while (old_grid[i] != NULL)
	{
		j = 0;
		while (old_grid[i][j].x != -2147483648)
		{
			new_grid[j][size.y].z = old_grid[i][j].z;
			new_grid[j][size.y].color = old_grid[i][j].color;
			new_grid[j][size.y].y -= new_grid[j][size.y].z
				* keep_z_change(-2147483648);
			j++;
		}
		size.y--;
		i++;
	}
}

static void	rotation_left(t_cd **old_grid, t_cd **new_grid)
{
	int		i;
	int		j;
	int		temp;
	t_cd	size;

	i = 0;
	size = grid_based_size(old_grid);
	while (old_grid[i] != NULL)
	{
		j = 0;
		temp = size.x - 1;
		while (old_grid[i][j].x != -2147483648)
		{
			new_grid[temp][i].z = old_grid[i][j].z;
			new_grid[temp][i].color = old_grid[i][j].color;
			new_grid[temp][i].y -= new_grid[temp][i].z
				* keep_z_change(-2147483648);
			temp--;
			j++;
		}
		i++;
	}
}

static void	replace_image(void **mlx, t_cd **grid, t_cd size)
{
	int		width;
	int		height;

	width = image_width(size, grid) + 6;
	height = image_height(size, grid) + 6;
	mlx_destroy_image(mlx[0], mlx[2]);
	mlx[2] = mlx_new_image(mlx[0], width, height);
	if (!mlx[2])
	{
		perror("Error creating image");
		ptr_ptr_free((void **)grid);
		exit(0);
	}
}

void	ft_rotate(void **mlx, int key)
{
	t_cd	**grid;
	t_cd	size;
	int		temp;

	size = grid_based_size(keep_grid(NULL));
	temp = size.x;
	size.x = size.y;
	size.y = temp;
	if (ft_prep_base_grid(size, 0, &grid) == NULL)
	{
		ptr_ptr_free((void **)keep_grid(NULL));
		exit (0);
	}
	if (key == 123)
		rotation_left(keep_grid(NULL), grid);
	else if (key == 124)
		rotation_right(keep_grid(NULL), grid);
	ptr_ptr_free((void **) keep_grid(NULL));
	replace_image(mlx, grid, size);
	keep_grid(grid);
	ft_drawing(grid, mlx);
}
