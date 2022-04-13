/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pantry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 12:53:53 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 12:55:34 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

t_cd	**keep_grid(t_cd **grid)
{
	static t_cd	**save;

	if (grid != NULL)
	{
		save = grid;
		return (NULL);
	}
	return (save);
}

t_cd	keep_xy_image(int x, int y)
{
	static t_cd	new_xy;

	if (x != -2147483648 && y != -2147483648)
	{
		new_xy.x = x;
		new_xy.y = y;
	}
	return (new_xy);
}

int	keep_z_change(int new_z_change)
{
	static int	z_change = 1;

	if (new_z_change == -2147483648)
		return (z_change);
	else
		z_change = new_z_change;
	return (0);
}
