/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/02 17:49:51 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int	step_by_step(t_cub *cub_data)
// {
// }

int	raycasting(t_cub *cub_data)
{
	int		i;
	int		step[2];
	int		map[2];
	double	cameraX;
	double	raydir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	plane[2];

	i = -1;
	while (++i < SCREENWIDTH)
	{
		//raycasting
		plane[X] = 0;
		plane[Y] = 0.66;
		cameraX = (i * 2) / (SCREENWIDTH - 1);
		raydir[X] = cub_data->dir[X] + plane[X] * cameraX;
		raydir[Y] = cub_data->dir[Y] + plane[Y] * cameraX;

		// calculo delta_dist y side_dist
		if (raydir[X] == 0)
			delta_dist[X] = fabs(1 / 1e30);
		else
			delta_dist[X] = fabs(1 / raydir[X]);
		if (raydir[Y] == 0)
			delta_dist[Y] = fabs(1 / raydir[Y]);
		else
			delta_dist[Y] = fabs(1 / raydir[Y]);
		
		map[X] = (int)cub_data->pos[X];
		map[Y] = (int)cub_data->pos[Y];
		if (raydir[X] < 0)
			(step[X] = -1, side_dist[X] = (cub_data->pos[X] - map[X]) * delta_dist[X]);
		else
			(step[X] = 1, side_dist[X] = (map[X] + 1 - cub_data->pos[X]) * delta_dist[X]);
		if (raydir[Y] < 0)
			(step[Y] = -1, side_dist[Y] = (cub_data->pos[Y] - map[Y]) * delta_dist[Y]);
		else
			(step[Y] = 1, side_dist[Y] = (map[Y] + 1 - cub_data->pos[Y]) * delta_dist[Y]);

		// step by step
		int hit;
		double perpWallDist;
		hit = 0; 
		while (hit == 0)
		{
			if (side_dist[X] < side_dist[Y])
			{
				side_dist[X] += delta_dist[X];
				map[X] += step[X];
				perpWallDist = (side_dist[X] - delta_dist[X]);
			}
			else
			{
				side_dist[Y] += delta_dist[Y];
				map[Y] += step[Y];
				perpWallDist = (side_dist[Y] - delta_dist[Y]);
			}
			if (cub_data->map_data->map[map[X]][map[Y]] < 0)
				hit = 1;
		}
	}
	return (EXIT_SUCCESS);
}
