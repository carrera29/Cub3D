/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:17:04 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/30 20:47:57 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim(char *line)
{
	char	*trim_line;

	if (*line == '\n')
		return (line);
	trim_line = ft_strtrim(line, " \n");
	free(line);
	return (trim_line);
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

t_map	*load_map_data(int fd)
{
	t_map	*map_data;
	char	*line;

	map_data = ft_calloc(1, sizeof(t_map));
	if (!map_data)
		error("malloc", true);
	line = trim(get_next_line(fd));
	if (!line)
		error(EMPTYFILE_ERROR, false);
	while (line && check_for_elements(map_data, line) != ALL_MASK)
		(free(line), line = trim(get_next_line(fd)));
	free(line);
	map_data->map = load_map(fd);
	if (!*map_data->map)
		error(EMPTYMAP_ERROR, false);
	check_map(map_data);
	close(fd);
	return (map_data);
}

t_cub	*initialization(char *file)
{
	t_cub	*cub_data;
	int		fd;

	cub_data = ft_calloc(1, sizeof(t_cub));
	if (!cub_data)
		error("malloc", true);
	if (ft_strncmp(ft_strrchr(file, '.'), ".cub\0", 4))
		error(EXT_ERROR, false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("open", true);
	cub_data->map_data = load_map_data(fd);
	return (cub_data);
}
