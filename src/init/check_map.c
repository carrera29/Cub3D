/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:06:41 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/24 18:13:05 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_map_size(int *width, int *height, char **map)
{
	int	i;
	int	max_len;
	int	line_len;

	i = -1;
	max_len = 0;
	while (map[++i])
	{
		line_len = ft_strlen(map[i]);
		if (line_len > max_len)
			max_len = line_len;
	}
	*width = max_len;
	*height = i;
	return (false);
}

static void	rearrange_map(char **map, int width)
{
	int	i;
	int	line_len;

	i = -1;
	while (map[++i])
	{
		line_len = ft_strlen(map[i]);
		map[i] = ft_realloc(map[i], line_len--, width + 1, sizeof(char));
		while (++line_len < width)
			map[i][line_len] = SPACE;
	}
}

static int	check_walls(char **map, int *size)
{
	char	*check_line;
	int		i;

	check_line = ft_strtrim(map[0], "1 ");
	if (*check_line)
		(free(check_line), error(WALL_ERROR, false));
	(free(check_line), check_line = ft_strtrim(map[size[HEIGHT] - 1], "1 "));
	if (*check_line)
		(free(check_line), error(WALL_ERROR, false));
	free(check_line);
	i = -1;
	while (map[++i])
		if ((map[i][0] != SPACE && map[i][0] != WALL) ||
		(map[i][size[WIDTH] - 1] != SPACE && map[i][size[WIDTH] - 1] != WALL))
			error(WALL_ERROR, false);
	return (false);
}

static int	check_initial_pos(t_map *map_data, char **map)
{
	int	i;
	int	j;
	int	floor_count;

	i = -1;
	floor_count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == NORTH || map[i][j] == SOUTH
				|| map[i][j] == EAST || map[i][j] == WEST)
			{
				if (map_data->pos)
					error(MAPNOTVALID_ERROR, false);
				map_data->pos = map[i][j];
			}
			if (map[i][j] == NOTHING)
				floor_count++;
		}
	}
	if (!floor_count || !map_data->pos)
		error(MAPNOTVALID_ERROR, false);
	return (false);
}

int	check_map(t_map *map_data)
{
	find_map_size(&map_data->size[WIDTH], &map_data->size[HEIGHT],
		map_data->map);
	rearrange_map(map_data->map, map_data->size[WIDTH]);
	check_walls(map_data->map, map_data->size);
	check_initial_pos(map_data, map_data->map);
	return (false);
}