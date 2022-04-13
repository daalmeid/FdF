/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_design.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:10:02 by daalmeid          #+#    #+#             */
/*   Updated: 2022/02/18 16:24:24 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdio.h>

static int	hexstring_to_int(char *hexsting)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	j = 0;
	num = 0;
	hexsting = &hexsting[2];
	while (hexsting[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		if (hexsting[i] >= 'a')
			num = num + (hexsting[i] - 87) * pow(16, j++);
		else if (hexsting[i] >= 'A')
			num = num + (hexsting[i] - 55) * pow(16, j++);
		else if (hexsting[i] >= '0')
			num = num + (hexsting[i] - 48) * pow(16, j++);
		i--;
	}
	return (num);
}

static int	z_addition(t_cd *grid_line, char *line)
{
	int		i;
	char	**z;
	char	*comma_ptr;

	i = 0;
	z = ft_split(line, ' ');
	if (!z)
	{
		perror("error splitting line");
		free(line);
		return (0);
	}
	while (z[i] != NULL && z[i][0] != '\n')
	{
		grid_line[i].z = ft_atoi(z[i]);
		grid_line[i].y -= ft_atoi(z[i]) * keep_z_change(-2147483648);
		grid_line[i].color = 0xffffff;
		comma_ptr = ft_strchr(z[i], ',');
		if (comma_ptr != NULL)
			grid_line[i].color = hexstring_to_int(++comma_ptr);
		i++;
	}
	ptr_ptr_free((void **) z);
	return (1);
}

t_cd	**ft_final_design(t_cd **grid, char *map)
{
	int		fd;
	char	*line;
	int		j;

	fd = file_dealer(-2, map);
	line = get_next_line(fd);
	j = 0;
	while (line != NULL)
	{
		if (!z_addition(grid[j], line))
		{	
			ptr_ptr_free((void **)grid);
			grid = NULL;
			break ;
		}
		j++;
		free (line);
		line = get_next_line(fd);
	}
	fd = file_dealer(fd, map);
	if (grid != NULL)
		keep_grid(grid);
	return (grid);
}
