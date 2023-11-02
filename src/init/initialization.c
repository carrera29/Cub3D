/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:17:04 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/02 19:51:56 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*trim(char *line)
{
	char	*trim_line;

	if (*line == '\n')
		return (line);
	trim_line = ft_strtrim(line, " \n");
	free(line);
	return (trim_line);
}

double	*initial_dir_vector(enum e_mapchar dir_char, double *vector)
{
	int				i;
	int				value;
	t_dir_vectors	dir_mask;
	const int		table[4][2] = {{'N', V_UP}, {'S', V_DOWN},
	{'W', V_LEFT}, {'E', V_RIGHT}};

	if (!dir_char)
		return (NULL);
	i = -1;
	while (++i < 4)
		if ((int)dir_char == table[i][0])
			dir_mask = table[i][1];
	value = ((dir_mask >> 2) & 1) | (((dir_mask >> 3) & 1) * 0x7FFFFFFF << 1);
	vector[X] = (double) value;
	value = (dir_mask & 1) | (((dir_mask >> 1) & 1) * 0x7FFFFFFF << 1);
	vector[Y] = (double) value;
	return (vector);
}

static int	check_for_elements(t_map *map_data, char **tex_path, char *line)
{
	static int	check;

	if (!ft_strncmp(line, "NO ", 3) && !(check & NO_MASK))
		(load_texture_filename(&tex_path[NORTH_TEX], line), check |= NO_MASK);
	else if (!ft_strncmp(line, "SO ", 3) && !(check & SO_MASK))
		(load_texture_filename(&tex_path[SOUTH_TEX], line), check |= SO_MASK);
	else if (!ft_strncmp(line, "WE ", 3) && !(check & WE_MASK))
		(load_texture_filename(&tex_path[WEST_TEX], line), check |= WE_MASK);
	else if (!ft_strncmp(line, "EA ", 3) && !(check & EA_MASK))
		(load_texture_filename(&tex_path[EAST_TEX], line), check |= EA_MASK);
	else if (!ft_strncmp(line, "S ", 2) && !(check & S_MASK))
		(load_texture_filename(&tex_path[SPRITE_TEX], line), check |= S_MASK);
	else if (!ft_strncmp(line, "F ", 2) && !(check & F_MASK))
		(load_rgb_color(&map_data->floor_color, line), check |= F_MASK);
	else if (!ft_strncmp(line, "C ", 2) && !(check & C_MASK))
		(load_rgb_color(&map_data->ceiling_color, line), check |= C_MASK);
	else if (*line != '\n' && *line != WALL)
		error(ELEM_ERROR, false);
	return (check);
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
	while (line && check_for_elements(map_data, map_data->texture_path, line)
		!= ALL_MASK)
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
	initial_dir_vector(cub_data->map_data->initial_dir, cub_data->dir);
	return (cub_data);
}
