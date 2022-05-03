/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:00:03 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 12:33:11 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"
#include "../headers/libft.h"
#include <stdio.h>

static t_cd	**alloc_grid(t_cd size)
{
	int		i;
	t_cd	**grid;

	i = 0;
	grid = malloc((sizeof(t_cd *) * size.y) + 1);
	if (!grid)
	{
		perror("Malloc failure during grid allocation");
		return (NULL);
	}
	while (i < size.y)
	{
		grid[i] = malloc((sizeof(t_cd) * size.x) + 1);
		if (!grid[i])
		{	
			ptr_ptr_free((void **) grid);
			perror("Malloc failure during grid allocation");
			return (NULL);
		}
		grid[i][size.x].x = -2147483648;
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

static int	get_scale(t_cd size, int z_change, int scale)
{
	int	aprox_height;

	scale += z_change * 2;
	if (scale != 0 && scale < 3)
		scale = 3;
	if (scale < 3)
	{
		aprox_height = 0;
		scale = 3;
		z_change = 1;
		aprox_height = (size.x - 1) * scale * sin(M_PI / 6);
		aprox_height += (size.y - 1) * scale * sin(M_PI / 6);
		while (aprox_height < 600)
		{
			scale += 2;
			aprox_height = (size.x - 1) * scale * sin(M_PI / 6);
			aprox_height += (size.y - 1) * scale * sin(M_PI / 6);
			if (z_change < 3)
				z_change++;
		}
		keep_z_change(z_change);
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

static void	correct_x(t_cd **grid, t_cd size)
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

t_cd	**ft_prep_base_grid(t_cd size, int z_change, t_cd ***grid)
{
	int			i;
	int			j;
	static int	scale = 0;

	scale = get_scale(size, z_change, scale);
	*grid = alloc_grid(size);
	if (!*grid)
		return (NULL);
	i = 1;
	first_line_grid(*grid, size, scale);
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			(*grid)[i][j].x = (*grid)[i - 1][j].x - (scale * cos(M_PI / 6));
			(*grid)[i][j].y = (*grid)[i - 1][j].y + (scale * sin(M_PI / 6));
			j++;
		}
		i++;
	}
	correct_x(*grid, size);
	return (*grid);
}
