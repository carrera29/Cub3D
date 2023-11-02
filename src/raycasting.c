/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/02 17:10:36 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// int	step_by_step(t_cub *cub_data)
// {
// }

// int	raycasting(t_cub *cub_data)
// {
// 	int i;
// 	int step[2];
// 	int map[2];
// 	double camaraX;
// 	double raydir[2];
// 	double sideDist[2];
// 	double deltaDist[2];
// 	double plane[2];

// 	i = -1;
// 	while (++i < SCREENWIDTH)
// 	{
// 		//raycating
// 		plane[X] = 0, plane[Y] = 0.66;
// 		camaraX = (i * 2) / (SCREENHEIGHT - 1);
// 		raydir[X] = cub_data->dir[X] + plane[X] * camaraX;
// 		raydir[Y] = cub_data->dir[Y] + plane[Y] * camaraX;

// 		// calculo deltaDist y sideDist
// 		if (raydir[X] == 0) 
// 			deltaDist[X] = fabs(1 / 1e30);
// 		else
// 			deltaDist[X] = fabs(1 / raydir[X]);
// 		if (raydir[X] == 0)
// 			deltaDist[Y] = fabs(1 / raydir[Y]);
// 		else
// 			deltaDist[Y] = fabs(1 / raydir[Y]);
		
// 		map[X] = (int)cub_data->pos[X];
// 		map[Y] = (int)cub_data->pos[Y];
// 		if (raydir[X] < 0)
// 			(step[X] = -1, sideDist[X] = (cub_data->pos[X] - map[X]) * deltaDist[X]);
// 		else
// 			(step[X] = 1, sideDist[X] = (map[X] + 1 - cub_data->pos[X]) * deltaDist[X]);
// 		if (raydir[Y] < 0)
// 			(step[Y] = -1, sideDist[Y] = (cub_data->pos[Y] - map[Y]) * deltaDist[Y]);
// 		else
// 			(step[Y] = 1, sideDist[Y] = (map[Y] + 1 - cub_data->pos[Y]) * deltaDist[Y]);

// 		// step by step
// 		int hit;
// 		double perpWallDist;
// 		hit = 0; 
// 		while (hit == 0)
// 		{
// 			if (sideDist[X] < sideDist[Y])
// 			{
// 				sideDist[X] += deltaDist[X];
// 				map[X] += step[X];
// 				perpWallDist = (sideDist[X] - deltaDist[X]);
// 			}
// 			else
// 			{
// 				sideDist[Y] += deltaDist[Y];
// 				map[Y] += step[Y];
// 				perpWallDist = (sideDist[Y] - deltaDist[Y]);
// 			}
// 			if (cub_data->map_data->map[map[X]][map[Y]] < 0)
// 				hit = 1;
// 		}
// 	}
// }