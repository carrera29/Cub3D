/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:37:46 by pollo             #+#    #+#             */
/*   Updated: 2023/10/16 15:30:37 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture_filename(char **texture, char *line)
{
	*texture = ft_strdup(ft_strnstr(line, "./", ft_strlen(line)));
}

void	load_rgb_color(int *color, char *line)
{
	char	**rgb;

	rgb = ft_split(line + 2, ',');
	if (!rgb || ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255
		|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255
		|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
		error("Bad syntax for RGB color(s)\n"
			"Correct syntax: [0-255], [0-255], [0-255]", false);
	*color = (ft_atoi(rgb[0]) << 16 | ft_atoi(rgb[1]) << 8 | ft_atoi(rgb[2]));
	ft_freedp(rgb);
}

static int	check_for_elements(t_map *map_data, char *line)
{
	static int	check_elements = 0;

	if (ft_strnstr(line, "NO ", ft_strlen(line)))
		(load_texture_filename(&map_data->north_texture, line),
			check_elements |= 0b1);
	else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		(load_texture_filename(&map_data->south_texture, line),
			check_elements |= 0b10);
	else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		(load_texture_filename(&map_data->west_texture, line),
			check_elements |= 0b100);
	else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		(load_texture_filename(&map_data->east_texture, line),
			check_elements |= 0b1000);
	else if (ft_strnstr(line, "F ", ft_strlen(line)))
		(load_rgb_color(&map_data->floor_color, line),
			check_elements |= 0b10000);
	else if (ft_strnstr(line, "C ", ft_strlen(line)))
		(load_rgb_color(&map_data->ceiling_color, line),
			check_elements |= 0b100000);
	if (check_elements == 0b00111111)
		return (true);
	return (false);
}

char	**load_map(int fd)
{
	char	**map;
	char	*line;
	int		i;

	map = ft_calloc(2, sizeof(char *));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (!ft_strncmp(line, "\n", 1))
		{
			(free(line), line = get_next_line(fd));
			continue ;
		}
		map[i++] = ft_strdup(line);
		map = ft_realloc(map, i + 1, i + 2, sizeof(char *));
		(free(line), line = get_next_line(fd));
	}
	return (map);
}

t_map	*load_map_data(int fd)
{
	t_map	*map_data;
	char	*line;

	map_data = ft_calloc(1, sizeof(t_map));
	if (!map_data)
		error("malloc", true);
	line = get_next_line(fd);
	if (!line)
		error("Empty file", false);
	while (line && !check_for_elements(map_data, line))
		(free(line), line = get_next_line(fd));
	if (!line)
		error("Element(s) missing", false);
	free(line);
	map_data->map = load_map(fd);
	if (!*map_data->map)
		error("Map content not found", false);
	return (map_data);
}
