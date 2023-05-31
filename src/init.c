/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:03:16 by pollo             #+#    #+#             */
/*   Updated: 2023/05/31 19:08:44 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	coordenates_x_y(t_map *map, int y, int x)
// {
// 	if ((y == 0) || !(map->map[y + 1][x])
// 		|| (x == 0) || !(map->map[y][x + 1]))
			
// 	return (0);
// }

// int	find_the_exit(t_map *map, int y, int x)
// {
// 	map->map[y][x] = '.';
// 	if (map->map[y + 1][x] != '1' && map->map[y + 1][x] != '.')
// 	{
// 		if (coordenates_x_y(map, y + 1, x) == 1)
// 			return (1);
// 		find_the_exit(map, y, (x + 1));
// 	}
// 	if (map->map[y][x + 1] != '1' && map->map[y][x + 1] != '.')
// 	{
// 		if (coordenates_x_y(map, y, x + 1) == 1)
// 			return (1);
// 		find_the_exit(map, y, (x + 1));
// 	}
// 	if (map->map[y - 1][x] != '1' && map->map[y - 1][x] != '.')
// 	{
// 		if (coordenates_x_y(map, y - 1, x) == 1)
// 			return (1);
// 		find_the_exit(map, (y - 1), x);
// 	}
// 	if (map->map[y][x - 1] != '1' && map->map[y][x - 1] != '.')
// 	{
// 		if (coordenates_x_y(map, y, x - 1) == 1)
// 			return (1);
// 		find_the_exit(map, y, (x - 1));
// 	}
// 	return (0);
// }

int	element_checker(t_map *map, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(map->p_x = x, map->p_y = y, map->p++);
	else if (c != '0' && c != '1')
		return (error_msg(map->cub, "Wrong map parameters\n"));
	if (c != 1 && (y == 0 || !(map->map[y + 1][x])
		|| x == 0 || !(map->map[y][x + 1])))
		return (error_msg(map->cub, "Map is not closed\n"));
	return (0);
}

int	check_char_to_char(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			if (element_checker(map, map->map[y][x], y, x))
				return (1);
	}
	if (map->p > 1 || map->p < 1)
		return (error_msg(map->cub, "Wrong character number"));
	return (0);
}


int	get_map(t_map *map, char *file)
{
	int		fd;
	char	*line;
	char	*add_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg(map->cub, "Error: fd"));
	add_line = "";
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		add_line = ft_strjoin(add_line, line);
		free(line);
	}
	map->map = ft_split(add_line, '\n');
	(free(line), free(add_line), close(fd));
	return (check_char_to_char(map));
}
