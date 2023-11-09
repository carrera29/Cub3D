/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:14:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/09 13:33:26 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define GRID_SIZE 20
#define EXTRA_GR 8

int	draw_grid(mlx_image_t *minimap, int i, int j, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < GRID_SIZE)
	{
		x = -1;
		while (++x < GRID_SIZE)
			mlx_put_pixel(minimap, x + j * GRID_SIZE, y + i * GRID_SIZE, color);
	}
	return (EXIT_SUCCESS);
}

mlx_image_t	*create_minimap(mlx_t *mlx, t_map *map_data)
{
	mlx_image_t	*minimap;
	int			i;
	int			j;

	minimap = mlx_new_image(mlx, (map_data->size[WIDTH] + EXTRA_GR) * GRID_SIZE,
			(map_data->size[HEIGHT] + EXTRA_GR) * GRID_SIZE);
	i = -1;
	while (++i < map_data->size[HEIGHT] + EXTRA_GR)
	{
		j = -1;
		while (++j < map_data->size[WIDTH] + EXTRA_GR)
			draw_grid(minimap, i, j, 0x6666FFFF);
	}
	i = -1;
	while (++i < map_data->size[HEIGHT])
	{
		j = -1;
		while (++j < map_data->size[WIDTH])
			if (map_data->map[i][j] != WALL)
				draw_grid(minimap, i + EXTRA_GR / 2,
					j + EXTRA_GR / 2, 0xFFFF99FF);
	}
	return (minimap);
}

int	minimap(t_cub *cub_data)
{
	static mlx_image_t	*minimap = 0;

	if (!minimap)
		minimap = create_minimap(cub_data->mlx, cub_data->map_data);
	return (EXIT_SUCCESS);
}
