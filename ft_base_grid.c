/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:00:03 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/14 17:02:57 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

static t_cd	**alloc_grid(t_cd size)
{
	int		i;
	t_cd	**grid;

	i = 0;
	grid = malloc((sizeof(t_cd *) * size.y) + 1);
	if (!grid)
	{
		write(2, "malloc failure\n", 16);
		return (NULL);
	}
	while (i < size.y)
	{
		grid[i] = malloc((sizeof(t_cd) * size.x) + 1);
		if (!grid[i])
		{	
			ptr_ptr_free((void **) grid);
			write(2, "malloc failure\n", 16);
			return (NULL);
		}
		grid[i][size.x].x = -2147483648;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

int	get_scale(t_cd size)
{
	int	aprox_height;
	int	scale;

	aprox_height = 0;
	scale = 3;
	aprox_height = (size.x - 1) * scale * sin(M_PI / 6);
	aprox_height += (size.y - 1) * scale * sin(M_PI / 6);
	while (aprox_height < 600)
	{
		scale += 2;
		aprox_height = (size.x - 1) * scale * sin(M_PI / 6);
		aprox_height += (size.y - 1) * scale * sin(M_PI / 6);
	}
	return (scale);
}

static void	first_line_grid(t_cd **grid, t_cd size, int scale)
{
	int	i;

	i = 1;
	grid[0][0].x = 0;
	grid[0][0].y = 0;
	while (i < size.x)
	{
		grid[0][i].x = scale * cos(M_PI / 6) + grid[0][i - 1].x;
		grid[0][i].y = scale * sin(M_PI / 6) + grid[0][i - 1].y;
		i++;
	}
}

void	correct_x(t_cd **grid, t_cd size)
{
	int		i;
	int		j;
	int		temp;

	i = 0;
	temp = grid[size.y - 1][0].x;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			grid[i][j].x -= (temp - 3);
			j++;
		}
		i++;
	}
}

t_cd	**ft_prep_base_grid(t_cd size, int zoom)
{
	int			i;
	int			j;
	static int	scale = 0;
	t_cd		**grid;

	scale += zoom;
	if (scale < 3)
		scale = get_scale(size);
	grid = alloc_grid(size);
	if (!grid)
		return (NULL);
	i = 1;
	first_line_grid(grid, size, scale);
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			grid[i][j].x = grid[i - 1][j].x - (scale * cos(M_PI / 6));
			grid[i][j].y = grid[i - 1][j].y + (scale * sin(M_PI / 6));
			j++;
		}
		i++;
	}
	correct_x(grid, size);
	return (grid);
}
