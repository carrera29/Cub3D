/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:06:41 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/21 03:10:52 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_size(int *width, int *height, char **map)
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
	return (true);
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
			map[i][line_len] = ' ';
	}
}

int	check_map(t_map *map_data)
{
	find_map_size(&map_data->size[WIDTH], &map_data->size[HEIGHT],
		map_data->map);
	rearrange_map(map_data->map, map_data->size[WIDTH]);
	check_walls(map_data->map, map_data->size);
	return (true);
}
