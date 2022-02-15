/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:14 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/14 17:00:50 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

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

int	file_dealer(int fd, char *map)
{
	if (fd == -2)
	{	
		fd = open(map, O_RDONLY);
		if (fd == -1)
		{
			write(2, "open() failed\n", 15);
			exit(0);
		}
	}
	else if (fd != -2)
	{
		if (close(fd) == -1)
		{
			write(2, "close() failed\n", 16);
			exit(0);
		}
		fd = -2;
	}
	return (fd);
}

void	ptr_ptr_free(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free (ptr[i++]);
	free(ptr);
}

t_data	handle_new_image(void **new)
{
	t_data	data;

	data.addr = mlx_get_data_addr(new[2], &data.bpp,
			&data.line_length, &data.endian);
	return (data);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)pixel = color;
}
