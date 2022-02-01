/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:02:20 by daalmeid          #+#    #+#             */
/*   Updated: 2022/01/31 13:23:24 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static void	line_draw(t_cd cd[], void **new, float b)
{
	float	slope;

	mlx_pixel_put(new[0], new[1], cd[0].x, cd[0].y, 0xffffff);
	while (cd[0].x != cd[1].x || cd[0].y != cd[1].y)
	{
		slope = (cd[0].y - cd[1].y) * cd[0].x + ((cd[0].x - cd[1].x)
				* -cd[0].y) + (cd[0].x - cd[1].x) * b;
		if ((slope > 0 && cd[0].y < cd[1].y)
			|| (slope < 0 && cd[0].y > cd[1].y) || cd[0].y == cd[1].y)
			cd[0].x++;
		else if (slope < 0 && (cd[0].y < cd[1].y || cd[0].x == cd[1].x))
			cd[0].y++;
		else if (slope > 0 && (cd[0].y > cd[1].y || cd[0].x == cd[1].x))
			cd[0].y--;
		else if (slope == 0)
		{
			cd[0].x++;
			if (cd[0].y < cd[1].y)
				cd[0].y++;
			else if (cd[0].y > cd[1].y)
				cd[0].y--;
		}
		mlx_pixel_put(new[0], new[1], cd[0].x, cd[0].y, 0xffffff);
	}
}

static void	prep_cd(t_cd cd[], void **new)
{
	float	b;
	float	slope;
	t_cd	temp;

	if (cd[0].x == cd[1].x)
	{
		while (cd[0].y != cd[1].y)
		{
			mlx_pixel_put(new[0], new[1], cd[0].x, cd[0].y, 0xffffff);
			if (cd[0].y > cd[1].y)
				cd[0].y--;
			else
				cd[0].y++;
		}
		return ;
	}
	b = ((cd[0].y - cd[1].y) * cd[0].x + (-(cd[0].x - cd[1].x) * cd[0].y))
		/ (float)(-(cd[0].x - cd[1].x));
	if (cd[0].x > cd[1].x)
	{
		temp = cd[0];
		cd[0] = cd[1];
		cd[1] = temp;
	}
	line_draw(cd, new, b);
}

int	ft_line_creation(int button, int x, int y, void *param)
{
	void		**new;
	static t_cd	cd[2];
	static int	i = 0;

	new = param;
	cd[i].x = x;
	cd[i].y = y;
	if (i++ == 1)
	{
		//printf("%d %d \n%d %d\n", cd[0].x, cd[0].y, cd[1].x, cd[1].y);
		prep_cd(cd, new);
		i = 0;
	}
	return (0);
}
