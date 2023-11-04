/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/04 07:33:17 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	step_by_step(t_ray *ry, char **map)
{
	int hit;
	hit = 0; 
	while (hit == 0)
	{
		if (ry->side_dist[X] < ry->side_dist[Y])
		{
			ry->side_dist[X] += ry->delta_dist[X];
			ry->map[X] += ry->step[X];
			ry->perpWallDist = ry->side_dist[X] - ry->delta_dist[X];
		}
		else
		{
			ry->side_dist[Y] += ry->delta_dist[Y];
			ry->map[Y] += ry->step[Y];
			ry->perpWallDist = ry->side_dist[Y] - ry->delta_dist[Y];
		}
		if (map[ry->map[X]][ry->map[Y]] == WALL)
			hit = 1;
	}
	return (EXIT_SUCCESS);
}

int	step_calculator(t_ray *ry, char coor, double pos)
{
	ry->delta_dist[coor] = fabs(1 / ry->raydir[coor]);
	ry->map[coor] = (int)pos;

	if (ry->raydir[coor] < 0)
	{
		ry->step[coor] = -1;
		ry->side_dist[coor] = (pos - ry->map[coor]) * ry->delta_dist[coor];
	}
	else
	{
		ry->step[coor] = 1;
		ry->side_dist[coor] = (ry->map[coor] + 1 - pos) * ry->delta_dist[coor];
	}
	return (EXIT_SUCCESS);
}

int	raycasting(t_cub *cub_data)
{
	t_ray	*ry;
	int		i;

	i = -1;
	while (++i < SCREENWIDTH)
	{
		ry->camera = i * 2 / (double)SCREENWIDTH - 1;
		ry->raydir[X] = cub_data->dir[X] + cub_data->plane[X] * ry->camera;
		if (ry->raydir[X] == 0)
			ry->raydir[X] = 1e30;
		ry->raydir[Y] = cub_data->dir[Y] + cub_data->plane[Y] * ry->camera;
		if (ry->raydir[Y] == 0)
			ry->raydir[Y] = 1e30;

		step_calculator(ry, X, cub_data->pos[X]);
		step_calculator(ry, Y, cub_data->pos[Y]);
		
		step_by_step(ry, cub_data->map_data->map);
	}
	return (EXIT_SUCCESS);
}
