/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:48:47 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/25 19:21:55 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_data(t_cub *cub_data)
{
	int	i;

	printf("NO path: %s\n", cub_data->map_data->texture_path[NORTH_TEX]);
	printf("SO path: %s\n", cub_data->map_data->texture_path[SOUTH_TEX]);
	printf("WE path: %s\n", cub_data->map_data->texture_path[WEST_TEX]);
	printf("EA path: %s\n", cub_data->map_data->texture_path[EAST_TEX]);
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
	i = -1;
	while (cub_data->map_data->map[++i])
		printf("%s\n", cub_data->map_data->map[i]);
}
