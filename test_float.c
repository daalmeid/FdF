/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:45:19 by daalmeid          #+#    #+#             */
/*   Updated: 2022/01/28 15:26:00 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

int	main(void)
{
	float	x;
	float	y;
	int		radius = 20;

	//cos(30graus) = x / 20;
	//sin(30graus) = y / 20;
	x = radius * cos(M_PI/6);
	y = radius * sin(M_PI/6);
	printf("x: %f, y: %f", x, y);
	return (0);
}