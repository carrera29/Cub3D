/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/14 23:50:33 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	*initialization(char *file)
{
	t_cub	*cub_data;
	int		fd;

	cub_data = ft_calloc(1, sizeof(cub_data));
	if (!cub_data)
		error("malloc", true);
	if (ft_strncmp(ft_strrchr(file, '.'), ".cub\0", 4))
		error("Extension not valid", false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("open", true);
	cub_data->map_data = load_map_data(fd);
	return (cub_data);
}

void	print_data(t_cub *cub_data)
{
	printf("NO path: %s", cub_data->map_data->north_texture);
	printf("SO path: %s", cub_data->map_data->south_texture);
	printf("WO path: %s", cub_data->map_data->west_texture);
	printf("EO path: %s", cub_data->map_data->east_texture);
		ft_putchar_fd('\n', STDOUT_FILENO);
	printf("Floor color: [%d][%d][%d]\n",
		(cub_data->map_data->floor_color >> 0x10) & 0xFF,
		(cub_data->map_data->floor_color >> 8) & 0xFF,
		cub_data->map_data->floor_color & 0xFF);
		ft_putchar_fd('\n', STDOUT_FILENO);
	printf("Ceiling color: [%d][%d][%d]\n",
		(cub_data->map_data->ceiling_color >> 0x10) & 0xFF,
		(cub_data->map_data->ceiling_color >> 8) & 0xFF,
		cub_data->map_data->ceiling_color & 0xFF);
		ft_putchar_fd('\n', STDOUT_FILENO);
	for (int i = 0; cub_data->map_data->map[i]; i++)
		printf("%s", cub_data->map_data->map[i]);

}

int	main(int argc, char **argv)
{
	t_cub	*cub_data;

	if (argc != 2)
		return (printf("Usage: ./cub3D [.cub extension map]\n"), EXIT_FAILURE);
	cub_data = initialization(argv[1]);
	print_data(cub_data);
	exit(EXIT_SUCCESS);
}
