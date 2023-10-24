/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:17:04 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/24 16:41:00 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		error(ELEM_ERROR, false);
	free(line);
	map_data->map = load_map(fd);
	check_map(map_data);
	return (map_data);
}

t_cub	*initialization(char *file)
{
	t_cub	*cub_data;
	int		fd;

	cub_data = ft_calloc(1, sizeof(cub_data));
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
