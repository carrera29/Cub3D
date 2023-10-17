/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:37:46 by pollo             #+#    #+#             */
/*   Updated: 2023/10/17 19:36:29 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture_filename(char **texture, char *line)
{
	*texture = ft_strdup(ft_strnstr(line, "./", ft_strlen(line)));
	ft_bzero(ft_strrchr(*texture, '\n'), 1);
}

static int	check_rgb_syntax(char *line)
{
	int	i;
	int	commas_count;

	i = 0;
	commas_count = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			commas_count++;
		if (line[i] != ',' && line[i] != ' '
			&& line[i] != '\n' && !ft_isdigit(line[i]))
			return (1);
	}
	if (commas_count != 2)
		return (1);
	return (0);
}

static void	load_rgb_color(int *color, char *line)
{
	char	**rgb_str;
	int		rgb[3];
	int		i;

	if (check_rgb_syntax(line))
		error(RGB_ERROR, false);
	rgb_str = ft_split(line + 2, ',');
	if (!rgb_str)
		error(RGB_ERROR, false);
	i = -1;
	while (rgb_str[++i])
		rgb[i] = ft_atoi(rgb_str[i]);
	if (rgb[0] < 0 || rgb[0] > 255 || (!rgb[0] && *rgb_str[0] != '0')
		|| rgb[1] < 0 || rgb[1] > 255 || (!rgb[1] && *rgb_str[1] != '0')
		|| rgb[2] < 0 || rgb[2] > 255 || (!rgb[2] && *rgb_str[2] != '0'))
		error(RGB_ERROR, false);
	*color = (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
	ft_freedp(rgb_str);
}

static int	check_for_elements(t_map *map_data, char *line)
{
	static int	check_elements = 0;

	if (!ft_strncmp(line, "NO ", 3))
		(load_texture_filename(&map_data->north_texture, line),
			check_elements |= 0b1);
	else if (!ft_strncmp(line, "SO ", 3))
		(load_texture_filename(&map_data->south_texture, line),
			check_elements |= 0b10);
	else if (!ft_strncmp(line, "WE ", 3))
		(load_texture_filename(&map_data->west_texture, line),
			check_elements |= 0b100);
	else if (!ft_strncmp(line, "EA ", 3))
		(load_texture_filename(&map_data->east_texture, line),
			check_elements |= 0b1000);
	else if (!ft_strncmp(line, "F ", 2))
		(load_rgb_color(&map_data->floor_color, line),
			check_elements |= 0b10000);
	else if (!ft_strncmp(line, "C ", 2))
		(load_rgb_color(&map_data->ceiling_color, line),
			check_elements |= 0b100000);
	if (check_elements == 0b00111111)
		return (true);
	return (false);
}

static char	**load_map(int fd)
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
		map[i] = ft_strdup(line);
		ft_bzero(ft_strrchr(map[i++], '\n'), 1);
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
		error(EMPTYFILE_ERROR, false);
	while (line && !check_for_elements(map_data, line))
		(free(line), line = get_next_line(fd));
	if (!line)
		error(MISSINGELEM_ERROR, false);
	free(line);
	map_data->map = load_map(fd);
	if (!*map_data->map)
		error(EMPTYMAP_ERROR, false);
	return (map_data);
}
