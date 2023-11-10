/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:14:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/11 00:22:16 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_minimap_hub(mlx_t *mlx)
{
	int			it[2];
	int			thick;
	mlx_image_t	*hub;

	hub = mlx_new_image(mlx, SCREENWIDTH / 5, SCREENWIDTH / 5);
	thick = 5;
	while (--thick)
	{
		it[X] = 0;
		while (++it[X] < (int)hub->width)
		{
			mlx_put_pixel(hub, it[X], thick, 0xFF);
			mlx_put_pixel(hub, it[X], hub->width - thick, 0xFF);
			mlx_put_pixel(hub, thick, it[X], 0xFF);
			mlx_put_pixel(hub, hub->width - thick, it[X], 0xFF);
		}
	}
	mlx_image_to_window(mlx, hub, SCREENWIDTH * 0.73, SCREENHEIGHT * 0.65);
	mlx_set_instance_depth(hub->instances, 2);
	return (EXIT_SUCCESS);
}

mlx_image_t	*init_minimap(mlx_t *mlx)
{
	mlx_image_t	*minimap;

	minimap = mlx_new_image(mlx, SCREENWIDTH / 5, SCREENWIDTH / 5);
	mlx_image_to_window(mlx, minimap, SCREENWIDTH * 0.73,
		SCREENHEIGHT * 0.65);
	mlx_set_instance_depth(minimap->instances, 1);
	return (minimap);
}

int	check_boundaries(double *map_pos, t_map *map_data)
{
	if (map_pos[X] >= map_data->size[WIDTH] || map_pos[X] < 0
		|| map_pos[Y] >= map_data->size[HEIGHT] || map_pos[Y] < 0)
		return (true);
	return (false);
}

int	minimap(t_cub *cub_data, mlx_t *mlx, t_map *map_data)
{
	double				map_pos[2];
	int					image_pos[2];
	static mlx_image_t	*minimap = 0;

	if (!minimap)
		minimap = init_minimap(mlx);
	image_pos[Y] = 0;
	map_pos[Y] = cub_data->pos[Y] - MINIMAP_TILES / 2.0;
	while (++image_pos[Y] < (int)minimap->height)
	{
		image_pos[X] = 0;
		map_pos[X] = cub_data->pos[X] + MINIMAP_TILES / 2.0;
		while (++image_pos[X] < (int)minimap->width)
		{
			mlx_put_pixel(minimap, image_pos[X], image_pos[Y], 0x0b5345ff);
			if (!check_boundaries(map_pos, map_data)
				&& map_data->map[(int)map_pos[Y]][(int)map_pos[X]] != WALL)
				mlx_put_pixel(minimap, image_pos[X], image_pos[Y], 0xfcf3cfff);
			map_pos[X] -= MINIMAP_TILES / (minimap->width - 1);
		}
		map_pos[Y] += MINIMAP_TILES / (minimap->height - 1);
	}
	return (EXIT_SUCCESS);
}