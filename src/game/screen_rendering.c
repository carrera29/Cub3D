/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:56:28 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/09 12:56:55 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_screen(t_cub *cub_data, t_ray ry, int screen_pos)
{
	int	i;

	i = -1;
	while (++i < SCREENHEIGHT)
	{
		if (i < ry.start_draw)
			mlx_put_pixel(cub_data->screen, screen_pos, i,
				cub_data->map_data->ceiling_color);
		else if (i > ry.end_draw)
			mlx_put_pixel(cub_data->screen, screen_pos, i,
				cub_data->map_data->floor_color);
		else
			mlx_put_pixel(cub_data->screen, screen_pos, i, 0x210d91FF);
	}
	return (EXIT_SUCCESS);
}

int	choose_texture(int side, double *pos, t_ray *ray)
{
	if (side == X)
	{
		if (ray->map[X] > pos[X])
			ray->wall_texture = WEST_TEX;
		else
			ray->wall_texture = WEST_TEX;
	}
	else if (side == Y)
	{
		if (ray->map[Y] > pos[Y])
			ray->wall_texture = SOUTH_TEX;
		else
			ray->wall_texture = NORTH_TEX;
	}
	return (EXIT_SUCCESS);
}
