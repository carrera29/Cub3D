/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:48:47 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/18 16:31:43 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_data(t_cub *cub_data)
{
	printf("NO path: %s\n", cub_data->map_data->north_texture);
	printf("SO path: %s\n", cub_data->map_data->south_texture);
	printf("WE path: %s\n", cub_data->map_data->west_texture);
	printf("EA path: %s\n", cub_data->map_data->east_texture);

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
		printf("%s\n", cub_data->map_data->map[i]);
}