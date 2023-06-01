/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/06/01 10:50:48 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	initialization(t_cub *cub, char *file)
{
	t_map	map;
	int		fd;

	(ft_memset(cub, 0, sizeof(cub)), ft_memset(&map, 0, sizeof(map)));
	(cub->map = &map, map.cub = cub);
	if (ft_strncmp(ft_strchr(file, '.'), ".cub\0", 5))
		return (error_msg(cub, "Wrong file name"));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg(cub, "Open fd"));
	if (get_map(&map, fd))
		return (1);
	find_the_exit(&map, map.p_y, map.p_x, '.');
	find_the_exit(&map, map.p_y, map.p_x, '0');
	map.map[map.p_y][map.p_x] = map.init_pos;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc == 2)
	{
		initialization(&cub, argv[1]);
	}
	return (0);
}
