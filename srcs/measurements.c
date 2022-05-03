/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measurements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:32:18 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 12:34:15 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"
#include "../headers/libft.h"
#include <stdio.h>

static void	correct_y(t_cd **grid, t_cd size, int y)
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

static int	find_height_low(t_cd size, t_cd **grid)
{
	int	i;
	int	j;
	int	height_low;

	i = 0;
	height_low = grid[0][0].y;
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
	return (height_low);
}

int	image_height(t_cd size, t_cd **grid)
{
	int	height_low;
	int	height_high;
	int	i;
	int	j;

	height_high = grid[size.y - 1][size.x - 1].y;
	height_low = find_height_low(size, grid);
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

int	image_width(t_cd size, t_cd **grid)
{
	int	width_low;
	int	width_high;

	width_low = grid[size.y - 1][0].x;
	width_high = grid[0][size.x - 1].x;
	return (width_high - width_low + 1);
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
