/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:03:57 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/01 18:54:01 by daalmeid         ###   ########.fr       */
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

t_cd	**prep_grid(t_cd **grid)
{
	int i;
	
	i = 0;
	grid = malloc((sizeof(t_cd *) * 12) + 1);
	if (!grid)
	{
		write(2, "malloc failure\n", 16);
		return (NULL);
	}
	while (i < 12)
	{
		grid[i] = malloc(sizeof(t_cd) * 19);
		if (!grid[i])
		{	
			i = 0;
			while (grid[i] != NULL)
				free (grid[i]);
			free (grid);
			write(2, "malloc failure\n", 16);
			return (NULL);
		}
		i++;
	}
	grid[i] = NULL;
	return (grid);
}

void	first_elem_grid(t_cd **grid)
{
	int 	count;

	count = 1;
	while (count < 19)
	{
		grid[0][count].x = 20 * cos(M_PI / 6) + grid[0][count - 1].x;
		grid[0][count].y = 20 * sin(M_PI / 6) + grid[0][count - 1].y;
		count++;
	}
}

t_cd	**prep_base_grid(void **new, char *line, int fd)
{
	int 	count;
	int 	i;
	t_cd	**grid;

	grid = prep_grid(grid);
	if (!grid)
		return (NULL);
	i = 1;
	grid[0][0].x = 960 - 180;
	grid[0][0].y = 540 - 110;
	first_elem_grid(grid);
	while (line != NULL) 
	{
		count = 0;
		while (count < 19)
		{
			grid[i][count].x = grid[i - 1][count].x - (20 * cos(M_PI / 6)); 
			grid[i][count].y = grid[i - 1][count].y + (20 * sin(M_PI / 6));
			count++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (grid);
}

t_cd	**final_design(void *new, t_cd **grid, char *map)
{
	int		fd;
	char	*line;
	char	**z;
	int		i;
	int		j = 0;
	int		to_free = 0;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write(2, "open() failed\n", 15);
		return (NULL);
	}
	while (line != NULL)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (grid);
		}
		z = ft_split(line, ' ');
		if (!z)
		{
			free (line);
			close(fd);
			return (NULL);
		}
		while (z[i] != NULL)
		{
			grid[j][i].y -= ft_atoi(z[i]);
			i++;
		}
		while (z[to_free] != NULL)
			free(z[to_free++]);
		free(z);
		free(line);
		j++;
		to_free = 0;
	}
	if (close(fd) == -1)
	{
		write(2, "close() failed\n", 16);
		return (NULL);
	}
	return (grid);
}

int	main(int ac, char **av)
{
	void	*new[2];
	int		fd;
	int		y = 0;
	char	*line;
	t_cd	**grid;

	if (ac != 2)
		return (0);
	new[0] = mlx_init();
	new[1] = mlx_new_window(new[0], 1920, 1080, "Test");
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
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "open() failed\n", 15);
		return (0);
	}
	line = get_next_line(fd);
	grid = prep_base_grid(new, line, fd);
	if (grid == NULL || final_design(new, grid, av[1]) == 0)
	{
		write(2, "Error creating grid.\n", 22);
		return (0);
	}
	ft_drawing(grid, new);
	while (y < 13)
		free(grid[y++]);
	free(grid);
	if (close(fd) == -1)
	{
		write(2, "close() failed\n", 16);
		return (0);
	}
	mlx_loop(new[0]);
	return (0);
}
