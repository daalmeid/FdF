/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_creation_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:22:06 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 12:33:40 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"
#include "../headers/libft.h"

static void	real_line_draw(t_cd cd[], float b)
{
	float	slope;

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
}

static int	pixel_nbr(t_cd cd[], float b, int *i)
{
	*i = 0;
	while (cd[0].x != cd[1].x || cd[0].y != cd[1].y)
	{
		real_line_draw(cd, b);
		(*i)++;
	}
	return (*i);
}

static void	prep_line_draw(t_cd cd[], float b, t_data img_data)
{
	int		i;
	t_cd	temp[2];

	temp[0] = cd[0];
	temp[1] = cd[1];
	my_pixel_put(&img_data, cd[0].x, cd[0].y, cd[0].color);
	i = (cd[0].color - cd[1].color) / pixel_nbr(temp, b, &i);
	while (cd[0].x != cd[1].x || cd[0].y != cd[1].y)
	{
		real_line_draw(cd, b);
		cd[0].color -= i;
		my_pixel_put(&img_data, cd[0].x, cd[0].y, cd[0].color);
	}
}

static void	prep_cd(t_cd cd[], t_data img_data)
{
	float	b;
	t_cd	temp;

	if (cd[0].x == cd[1].x)
	{
		while (cd[0].y != cd[1].y)
		{
			my_pixel_put(&img_data, cd[0].x, cd[0].y, cd[0].color);
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
	prep_line_draw(cd, b, img_data);
}

int	ft_line_creation(int x, int y, unsigned int color, void *param)
{
	void		**mlx;
	static t_cd	cd[2];
	static int	i = 0;
	t_data		img_data;

	mlx = param;
	cd[i].x = x;
	cd[i].y = y;
	cd[i].color = color;
	if (i++ == 1)
	{
		img_data = handle_new_image(mlx);
		prep_cd(cd, img_data);
		i = 0;
	}
	return (0);
}
