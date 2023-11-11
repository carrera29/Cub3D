/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 20:14:28 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/11 20:14:48 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*init_minimap(mlx_t *mlx)
{
	mlx_image_t	*minimap;

	minimap = mlx_new_image(mlx, SCREENWIDTH / 5, SCREENWIDTH / 5);
	mlx_image_to_window(mlx, minimap, SCREENWIDTH * 0.73,
		SCREENHEIGHT * 0.65);
	mlx_set_instance_depth(minimap->instances, 1);
	return (minimap);
}

mlx_image_t	*init_arrow(mlx_t *mlx, mlx_image_t *minimap)
{
	mlx_image_t	*arrow;

	arrow = mlx_new_image(mlx, minimap->width / 5, minimap->height / 5);
	mlx_image_to_window(mlx, arrow, minimap->instances->x
		+ (minimap->width - arrow->width) / 2, minimap->instances->y
		+ (minimap->height - arrow->height) / 2);
	mlx_set_instance_depth(arrow->instances, 3);
	return (arrow);
}

int	check_boundaries(double *map_pos, t_map *map_data)
{
	if (map_pos[X] >= map_data->size[WIDTH] || map_pos[X] < 0
		|| map_pos[Y] >= map_data->size[HEIGHT] || map_pos[Y] < 0)
		return (true);
	return (false);
}