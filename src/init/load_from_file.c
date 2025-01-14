/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:37:46 by pollo             #+#    #+#             */
/*   Updated: 2023/11/24 19:43:00 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture_filename(char **texture, char *line)
{
	int	test_fd;

	*texture = ft_strdup(ft_strchr(line, '.'));
	if (ft_strncmp(ft_strrchr(*texture, '.'), ".xpm42\0", 7))
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
		if (line[i] != ',' && line[i] != ' '
			&& line[i] != '\n' && !ft_isdigit(line[i]))
			return (true);
	}
	if (commas_count != 2)
		return (true);
	return (false);
}

void	load_rgb_color(int *color, char *line)
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
	ft_freedp((void **)rgb_str, 0);
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
		is_map = ft_strtrim(line, "NSEW01D ");
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
