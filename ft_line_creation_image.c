/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_creation_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:22:06 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/15 12:21:15 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static int	pixel_nbr(t_cd cd[], float b, int *i)
{
	float	slope;

	*i = 0;
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
		(*i)++;
	}
	return (*i);
}

static void	real_line_draw(t_cd cd[], float b)
{
	float	slope;
	
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
	}
}

static void	line_draw(t_cd cd[], float b, t_data img_data)
{
	float	slope;
	int		i;
	t_cd	temp[2];

	temp[0] = cd[0];
	temp[1] = cd[1];
	my_pixel_put(&img_data, cd[0].x, cd[0].y, cd[0].color);
	i = (cd[0].color - cd[1].color) / pixel_nbr(temp, b, &i);
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
		cd[0].color -= i;
		my_pixel_put(&img_data, cd[0].x, cd[0].y, cd[0].color);
	}
}

static void	prep_cd(t_cd cd[], void **new)
{
	float	b;
	t_cd	temp;
	t_data	img_data;

	img_data = handle_new_image(new);
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
	line_draw(cd, b, img_data);
}

int	ft_line_creation(int x, int y, unsigned int color, void *param)
{
	void		**new;
	static t_cd	cd[2];
	static int	i = 0;

	new = param;
	cd[i].x = x;
	cd[i].y = y;
	cd[i].color = color;
	if (i++ == 1)
	{
		prep_cd(cd, new);
		i = 0;
	}
	return (0);
}
