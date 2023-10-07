/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:37:46 by pollo             #+#    #+#             */
/*   Updated: 2023/10/07 18:11:10 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	coordenates_x_y(t_map *map, int y, int x)
{
	if (y == 0 || !(map->map[y + 1])
		|| x == 0 || !(map->map[y][x + 1]))
		exit (error_msg(map->cub, "Map is open"));
}

int	find_the_exit(t_map *map, int y, int x, char c)
{
	map->map[y][x] = c;
	if (map->map[y + 1][x] != '1' && map->map[y + 1][x] != c)
		(coordenates_x_y(map, y + 1, x), find_the_exit(map, (y + 1), x, c));
	if (map->map[y][x + 1] != '1' && map->map[y][x + 1] != c)
		(coordenates_x_y(map, y, x + 1), find_the_exit(map, y, (x + 1), c));
	if (map->map[y - 1][x] != '1' && map->map[y - 1][x] != c)
		(coordenates_x_y(map, y - 1, x), find_the_exit(map, (y - 1), x, c));
	if (map->map[y][x - 1] != '1' && map->map[y][x - 1] != c)
		(coordenates_x_y(map, y, x - 1), find_the_exit(map, y, (x - 1), c));
	return (0);
}

int	element_checker(t_map *map, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(map->pos[Y] = y, map->pos[X] = x, map->blaz++, map->c_init = c);
	else if (c != '0' && c != '1')
		return (error_msg(map->cub, "Wrong map parameters"));
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
	(map->height = y, map->width = x);
	if (map->blaz > 1 || map->blaz < 1)
		return (error_msg(map->cub, "Wrong character number"));
	return (0);
}

int	get_map(t_map *map, int fd)
{
	char	*line;
	char	*add_line;

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