/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 01:06:41 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/21 01:29:43 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_size(int **map_size, char **map)
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
	*map_size[WIDTH] = max_len;
	*map_size[HEIGHT] = i;
	return (true);
}

int	check_map(t_map *map_data)
{
	find_map_size(&map_data->size, map_data->map);
	return (true);
}
