/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:05:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 16:45:56 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

static void	wasd_esc_handler(int key, void **mlx, int *x, int *y)
{
	if (key == 53)
	{	
		ptr_ptr_free((void **) keep_grid(NULL));
		mlx_destroy_image(mlx[0], mlx[2]);
		mlx_destroy_window(mlx[0], mlx[1]);
		exit(0);
	}
	else if ((key >= 0 && key <= 2) || key == 13)
	{
		mlx_clear_window(mlx[0], mlx[1]);
		if (key == 0)
			mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], *x -= 10, *y);
		else if (key == 2)
			mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], *x += 10, *y);
		else if (key == 1)
			mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], *x, *y += 10);
		else if (key == 13)
			mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], *x, *y -= 10);
	}
}

static void	redraw_window(void **mlx, int x, int y)
{
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], x, y);
	put_instructions(mlx, x, y, -1);
}

int	key_handler(int key, void *param)
{
	void		**mlx;
	static int	x = 50;
	static int	y = 50;

	mlx = param;
	wasd_esc_handler(key, mlx, &x, &y);
	if (key == 69 || key == 24)
	{
		zoom_handler(mlx, 1, &x, &y);
		redraw_window(mlx, x, y);
	}
	else if (key == 78 || key == 27)
	{
		zoom_handler(mlx, -1, &x, &y);
		redraw_window(mlx, x, y);
	}
	else if (key == 123 || key == 124)
	{
		ft_rotate(mlx, key);
		redraw_window(mlx, x, y);
	}
	else if (key == 34)
		put_instructions(mlx, x, y, 0);
	keep_xy_image(x, y);
	return (0);
}
