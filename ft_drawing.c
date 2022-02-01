/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:25:04 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/01 16:21:45 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

void	ft_drawing(t_cd **grd, void **new)
{
	int	i;
	int	count;

	i = 0;
	while (grd[i] != NULL)
	{
		count = 0;
		while (count < 18)
		{
			ft_line_creation(0, grd[i][count].x, grd[i][count].y, new);
			count++;
			ft_line_creation(0, grd[i][count].x, grd[i][count].y, new);
		}
		i++;
		if (grd[i] == NULL)
			break ;
		count = 0;
		while (count < 19)
		{
			ft_line_creation(0, grd[i - 1][count].x, grd[i - 1][count].y, new);
			ft_line_creation(0, grd[i][count].x, grd[i][count].y, new);
			count++;
		}
	}
}
