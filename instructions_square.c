/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_square.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:08:20 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 16:49:42 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

static void	window_clearer(void **mlx, int x, int y)
{
	int	i;
	int	j;

	i = 10;
	while (i < y)
	{
		j = 10;
		while (j < x)
		{
			mlx_pixel_put(mlx[0], mlx[1], j, i, 0x000000);
			j++;
		}
		i++;
	}
}

static void	square_draw(void **mlx)
{
	int	i;
	int	j;

	i = 10;
	while (i <= 200)
	{
		j = 10;
		while (j <= 180 && (i == 10 || i == 200))
		{
			mlx_pixel_put(mlx[0], mlx[1], j, i, 0xffffff);
			j++;
		}
		mlx_pixel_put(mlx[0], mlx[1], 10, i, 0xffffff);
		mlx_pixel_put(mlx[0], mlx[1], 180, i, 0xffffff);
		i++;
	}
	mlx_string_put(mlx[0], mlx[1], 35, 20, 0xffffff, "Instructions");
	mlx_string_put(mlx[0], mlx[1], 15, 50, 0xffffff, "Open this");
	mlx_string_put(mlx[0], mlx[1], 25, 70, 0xffffff, "window : <i>;");
	mlx_string_put(mlx[0], mlx[1], 15, 90, 0xffffff, "Zoom: +/-;");
	mlx_string_put(mlx[0], mlx[1], 15, 110, 0xffffff, "Move: WASD;");
	mlx_string_put(mlx[0], mlx[1], 15, 130, 0xffffff, "Change Z: Wheel;");
	mlx_string_put(mlx[0], mlx[1], 15, 150, 0xffffff, "Rotate: <-/->;");
	mlx_string_put(mlx[0], mlx[1], 15, 170, 0xffffff, "Exit: ESC;");
}

void	put_instructions(void **mlx, int x, int y, int zero_out)
{
	static int	i = 0;	

	if (zero_out == -1)
		i = 0;
	else if (i == 0)
	{
		window_clearer(mlx, 181, 201);
		square_draw(mlx);
		i++;
	}
	else if (i == 1)
	{
		i = 0;
		mlx_clear_window(mlx[0], mlx[1]);
		mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], x, y);
	}
}
