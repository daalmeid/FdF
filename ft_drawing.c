/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:25:04 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/14 17:04:52 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

void	ft_drawing(t_cd **grd, void **new)
{
	int	i;
	int	j;

	i = 0;
	while (grd[i] != NULL)
	{
		j = 0;
		while (grd[i][j + 1].x != -2147483648)
		{
			ft_line_creation(grd[i][j].x, grd[i][j].y, grd[i][j].color, new);
			j++;
			ft_line_creation(grd[i][j].x, grd[i][j].y, grd[i][j].color, new);
		}
		i++;
		if (grd[i] == NULL)
			break ;
		j = 0;
		while (grd[i][j].x != -2147483648)
		{
			ft_line_creation(grd[i - 1][j].x, grd[i - 1][j].y, grd[i][j].color,
				new);
			ft_line_creation(grd[i][j].x, grd[i][j].y, grd[i][j].color, new);
			j++;
		}
	}
}
