/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:03:57 by daalmeid          #+#    #+#             */
/*   Updated: 2022/01/28 16:59:48 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

int	key_print(int key, void *param)
{
	ft_putnbr_fd(key, 1);
	ft_putchar_fd(' ', 1);
	if (key == 53)
		exit(0);
	return (0);
}

int	point_connection(void **new, char *line, int fd)
{
	int	x = 320;
	int	y = 400;
	int	j = 0;
	int	k = 0;

	while (line != NULL)
	{
		j = 360 * cos(M_PI / 6) + x;
		k = 360 * sin(M_PI / 6) + y;
		ft_line_creation(0, x, y, new);
		ft_line_creation(0, j, k, new);
		free(line);
		line = get_next_line(fd);
		printf("%s\n", line);
		y += 20 * sin(M_PI / 6);
		x -= 20 * cos(M_PI / 6); 
	}
	return (0);
}

int	main(void)
{
	void	*new[2];
	int		i = 100;
	int		y = 0;
	char	*line;

	new[0] = mlx_init();
	new[1] = mlx_new_window(new[0], 1000, 1000, "Test");
	/*while (i < 901)
	{
		mlx_pixel_put(new[0], new[1], i, 500 + y, 0xffffff);
		mlx_pixel_put(new[0], new[1], i, 500 - y, 0xffffff);
		i++;
		if (y == 400)
			y = -400;
		y++;
	}
	y = 100;
	while (y < 900)
	{	
		mlx_pixel_put(new[0], new[1], 500, y, 0xffffff);
		mlx_pixel_put(new[0], new[1], y++, 500, 0xffffff);
	}*/
	mlx_key_hook(new[1], key_print, (void *) 0);
	mlx_mouse_hook(new[1], ft_line_creation, new);
	i = open("./test_maps/42.fdf", O_RDONLY);
	line = get_next_line(i);
	point_connection(new, line, i);
	close(i);
	mlx_loop(new[0]);
	return (0);
}
