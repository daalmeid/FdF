/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:14 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 16:35:13 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

void	ptr_ptr_free(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free (ptr[i++]);
	free(ptr);
}

int	file_dealer(int fd, char *map)
{
	if (fd == -2)
	{	
		fd = open(map, O_RDONLY);
		if (fd == -1)
		{
			perror("open() failed");
			exit(0);
		}
	}
	else if (fd != -2)
	{
		if (close(fd) == -1)
		{
			perror("close() failed");
			exit(0);
		}
		fd = -2;
	}
	return (fd);
}

t_data	handle_new_image(void **mlx)
{
	t_data	data;

	data.addr = mlx_get_data_addr(mlx[2], &data.bpp,
			&data.line_length, &data.endian);
	return (data);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)pixel = color;
}
