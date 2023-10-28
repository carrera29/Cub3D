/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:37:46 by pollo             #+#    #+#             */
/*   Updated: 2023/10/28 17:48:54 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture_filename(char **texture, char *line)
{
	int	test_fd;

	*texture = ft_strdup(ft_strnstr(line, "./", ft_strlen(line)));
	ft_bzero(ft_strrchr(*texture, '\n'), 1);
	if (ft_strncmp(ft_strrchr(*texture, '.'), ".xpm\0", 5))
		error(TEXTURESYNTAX_ERROR, false);
	test_fd = open(*texture, O_RDONLY);
	if (test_fd < 0)
		error(TEXTUREPATH_ERROR, true);
	close(test_fd);
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
		if (line[i] != ',' && line[i] != SPACE
			&& line[i] != '\n' && !ft_isdigit(line[i]))
			return (true);
	}
	if (commas_count != 2)
		return (true);
	return (false);
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
	*color = (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0xFF);
	ft_freedp(rgb_str);
}

int	check_for_elements(t_map *map_data, char *line)
{
	static int	check_elements;

	if (!ft_strncmp(line, "NO ", 3) && !(check_elements & NO_MASK))
		(load_texture_filename(&map_data->texture_path[NORTH_TEX], line),
			check_elements |= NO_MASK);
	else if (!ft_strncmp(line, "SO ", 3) && !(check_elements & SO_MASK))
		(load_texture_filename(&map_data->texture_path[SOUTH_TEX], line),
			check_elements |= SO_MASK);
	else if (!ft_strncmp(line, "WE ", 3) && !(check_elements & WE_MASK))
		(load_texture_filename(&map_data->texture_path[WEST_TEX], line),
			check_elements |= WE_MASK);
	else if (!ft_strncmp(line, "EA ", 3) && !(check_elements & EA_MASK))
		(load_texture_filename(&map_data->texture_path[EAST_TEX], line),
			check_elements |= EA_MASK);
	else if (!ft_strncmp(line, "S ", 2) && !(check_elements & S_MASK))
		(load_texture_filename(&map_data->texture_path[SPRITE_TEX], line),
			check_elements |= S_MASK);
	else if (!ft_strncmp(line, "F ", 2) && !(check_elements & F_MASK))
		(load_rgb_color(&map_data->floor_color, line),
			check_elements |= F_MASK);
	else if (!ft_strncmp(line, "C ", 2) && !(check_elements & C_MASK))
		(load_rgb_color(&map_data->ceiling_color, line),
			check_elements |= C_MASK);
	else if (*line != '\n' && *line != WALL)
		error(ELEM_ERROR, false);
	return (check_elements);
}

char	**load_map(int fd)
{
	char	**map;
	char	*line;
	char	*is_map;
	int		i;

	map = ft_calloc(2, sizeof(char *));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (*line == '\n')
		{
			(free(line), line = get_next_line(fd));
			continue ;
		}
		is_map = ft_strtrim(line, "NSEW01 ");
		if (*is_map != '\n' && *is_map)
			error(ELEM_ERROR, false);
		free(is_map);
		map[i] = ft_strdup(line);
		ft_bzero(ft_strrchr(map[i++], '\n'), 1);
		map = ft_realloc(map, i + 1, i + 2, sizeof(char *));
		(free(line), line = get_next_line(fd));
	}
	return (map);
}
