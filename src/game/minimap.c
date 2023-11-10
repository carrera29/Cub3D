/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:14:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/10 10:36:44 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_grid(mlx_image_t *minimap, int i, int j, int color)
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
	while (++i < (int)minimap->height / GRID_SIZE)
	{
		j = -1;
		while (++j < (int)minimap->width / GRID_SIZE)
			draw_grid(minimap, i, j, 0x6666FFFF);
	}
	i = -1;
	while (++i < map_data->size[HEIGHT])
	{
		j = -1;
		while (++j < map_data->size[WIDTH])
			if (map_data->map[i][j] != WALL)
				draw_grid(minimap, i + EXTRA_GR / 2, minimap->width / GRID_SIZE
					- (j + EXTRA_GR / 2), 0xFFFF99FF);
	}
	return (minimap);
}

int	draw_circle(mlx_image_t *screen)
{
	int	i;
	int	j;
	int	minimap_pos[2];

	i = -1;
	j = -1;
	minimap_pos[X] = SCREENHEIGHT - (SCREENHEIGHT / 4);
	minimap_pos[Y] = SCREENWIDTH - (SCREENWIDTH / 4);
	while (++i <= CIRCLE_RADIUS)
	{
		j = -i - 1;
		while (++j < i)
			mlx_put_pixel(screen, minimap_pos[Y] + j,
				minimap_pos[X] + i, 0xFF000000);
	}
	return (EXIT_SUCCESS);
}

int	minimap(t_cub *cub_data)
{
	draw_circle(cub_data->screen);
	return (EXIT_SUCCESS);
}
