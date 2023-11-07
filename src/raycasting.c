/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/07 22:27:41 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_height(t_ray *ry)
{
	int	line_height;

	line_height = (int)(SCREENHEIGHT / ry->perpWallDist);
	ry->start_draw = (-line_height / 2) + (SCREENHEIGHT / 2);
	if (ry->start_draw < 0)
		ry->start_draw = 0;
	ry->end_draw = (line_height / 2) + (SCREENHEIGHT / 2);
	if (ry->end_draw >= SCREENHEIGHT)
		ry->end_draw = SCREENHEIGHT - 1;
	return (EXIT_SUCCESS);
}

int	step_by_step(t_ray *ry, char **map)
{
	int	hit;

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
		if (map[ry->map[Y]][ry->map[X]] == WALL)
			hit = 1;
	}
	return (EXIT_SUCCESS);
}

int	step_calculator(t_ray *ry, double *pos)
{
	int	i;

	i = -1;
	while (++i <= Y)
	{
		ry->delta_dist[i] = fabs(1 / ry->raydir[i]);
		ry->map[i] = (int)pos[i];
		if (ry->raydir[i] < 0)
		{
			ry->step[i] = -1;
			ry->side_dist[i] = (pos[i] - ry->map[i]) * ry->delta_dist[i];
		}
		else
		{
			ry->step[i] = 1;
			ry->side_dist[i] = (ry->map[i] + 1 - pos[i]) * ry->delta_dist[i];
		}
	}
	return (EXIT_SUCCESS);
}

int	paint_color(t_cub *cub_data, t_ray *ry, int screen_pos)
{
	int	i;

	i = -1;
	while (++i < (int) cub_data->line[screen_pos]->height)
	{
		mlx_put_pixel(cub_data->line[i], 0, i, 0);
		if (i >= ry->start_draw && i <= ry->end_draw)
			mlx_put_pixel(cub_data->line[i], 0, i, 0x210d91);
	}
	mlx_image_to_window(cub_data->mlx, cub_data->line[screen_pos], screen_pos, 0);
	return (EXIT_SUCCESS);
}

int	raycasting(t_cub *cub_data)
{
	t_ray	ry;
	int		i;

	i = -1;
	while (++i < SCREENWIDTH)
	{
		ry.camera = i * 2 / (double)SCREENWIDTH - 1;
		ry.raydir[X] = cub_data->dir[X] + cub_data->plane[X] * ry.camera;
		ry.raydir[Y] = cub_data->dir[Y] + cub_data->plane[Y] * ry.camera;
		step_calculator(&ry, cub_data->pos);
		step_by_step(&ry, cub_data->map_data->map);
		wall_height(&ry);
		paint_color(cub_data, &ry, i);
	}
	cub_data->move_speed = cub_data->mlx->delta_time * 5.0;
	cub_data->rot_speed = cub_data->mlx->delta_time * 3.0;
	return (EXIT_SUCCESS);
}
