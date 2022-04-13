/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_clicks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 17:49:09 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 17:02:46 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

int	cross_handler(void *param)
{
	t_cd	**grid;
	void	**mlx;

	mlx = (void **) param;
	grid = keep_grid(NULL);
	ptr_ptr_free((void **) grid);
	mlx_destroy_image(mlx[0], mlx[2]);
	exit(0);
}

static void	z_altered_image_put(t_cd **grid, void *param)
{
	void	**mlx;
	t_cd	xy_image;
	int		width;
	int		height;

	mlx = (void **) param;
	width = image_width(grid_based_size(grid), grid);
	height = image_height(grid_based_size(grid), grid);
	xy_image = keep_xy_image(-2147483648, -2147483648);
	mlx_destroy_image(mlx[0], mlx[2]);
	mlx[2] = mlx_new_image(mlx[0], width + 6, height + 6);
	if (!mlx[2])
	{
		perror("Error creating image");
		ptr_ptr_free((void **) grid);
		exit(0);
	}
	ft_drawing(grid, mlx);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], xy_image.x, xy_image.y);
	xy_image = keep_xy_image(xy_image.x, xy_image.y);
	put_instructions(mlx, xy_image.x, xy_image.y, -1);
}

static int	get_z_up_or_down(int button)
{
	int	z_up_or_down;

	z_up_or_down = -1;
	if (button == 4)
		z_up_or_down = 1;
	return (z_up_or_down);
}

static int	prep_z_change(int button, int z_change)
{
	if (button == 4)
			z_change++;
	else
			z_change--;
	keep_z_change(z_change);
	return (z_change);
}

int	click_handler(int button, int x, int y, void *param)
{
	t_cd		**grid;
	int			z_up_or_down;
	static int	z_change = 1;

	if (button == 5 || button == 4)
	{
		z_change = keep_z_change(-2147483648);
		grid = keep_grid(NULL);
		y = 0;
		z_up_or_down = get_z_up_or_down(button);
		while (grid[y] != NULL)
		{
			x = 0;
			while (grid[y][x].x != -2147483648)
			{
				grid[y][x].y -= grid[y][x].z * z_up_or_down;
				x++;
			}
			y++;
		}
		z_change = prep_z_change(button, z_change);
		z_altered_image_put(grid, param);
	}
	return (0);
}
