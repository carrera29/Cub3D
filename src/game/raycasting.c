/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/16 18:10:19 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_height(t_ray *ry)
{
	ry->line_height = (int)(SCREENHEIGHT / ry->perp_wall_dist);
	ry->start_draw = (-ry->line_height / 2) + (SCREENHEIGHT / 2);
	if (ry->start_draw < 0)
		ry->start_draw = 0;
	ry->end_draw = (ry->line_height / 2) + (SCREENHEIGHT / 2);
	if (ry->end_draw >= SCREENHEIGHT)
		ry->end_draw = SCREENHEIGHT - 1;
	return (EXIT_SUCCESS);
}

int	raycasting_doors(t_ray *ry, double *pos)
{
	double	door_distance;

	door_distance = fabs(ry->delta_dist[ry->side]
			* (ry->ray_pos[ry->side] - pos[ry->side] + 0.5));
	if (ry->side_dist[ry->side ^ 1] < door_distance)
		ry->wall_texture = DOORJAM_TEX;
	else if (fabs(ry->side_dist[ry->side ^ 1] - door_distance) > 0.0001)
	{
		ry->wall_texture = DOOR_TEX;
		ry->perp_wall_dist += ry->delta_dist[ry->side] / 2;
		return (true);
	}
	return (false);
}

int	step_by_step(t_ray *ry, char **map, double *pos)
{
	int	hit;
	int	index;

	hit = 0;
	while (hit == 0)
	{
		index = Y;
		if (ry->side_dist[X] < ry->side_dist[Y])
			index = X;
		ry->perp_wall_dist = ry->side_dist[index];
		ry->side_dist[index] += ry->delta_dist[index];
		ry->ray_pos[index] += ry->step[index];
		ry->side = index;
		if (map[ry->ray_pos[Y]][ry->ray_pos[X]] == WALL)
			hit = 1;
		if (map[ry->ray_pos[Y]][ry->ray_pos[X]] == DOOR)
			hit = raycasting_doors(ry, pos);
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
		ry->ray_pos[i] = (int)pos[i];
		if (ry->raydir[i] < 0)
		{
			ry->step[i] = -1;
			ry->side_dist[i] = (pos[i] - ry->ray_pos[i])
				* ry->delta_dist[i];
		}
		else
		{
			ry->step[i] = 1;
			ry->side_dist[i] = (ry->ray_pos[i] + 1 - pos[i])
				* ry->delta_dist[i];
		}
	}
	return (EXIT_SUCCESS);
}

int	raycasting(t_cub *cub_data)
{
	t_ray	ry;
	int		i;

	i = -1;
	while (++i < SCREENWIDTH)
	{
		ft_memset(&ry, 0, sizeof(t_ray));
		ry.camera = i * 2 / (double)SCREENWIDTH - 1;
		ry.raydir[X] = cub_data->dir[X] + cub_data->plane[X] * ry.camera;
		ry.raydir[Y] = cub_data->dir[Y] + cub_data->plane[Y] * ry.camera;
		step_calculator(&ry, cub_data->pos);
		step_by_step(&ry, cub_data->map_data->map, cub_data->pos);
		select_texture(&ry, cub_data->pos);
		wall_height(&ry);
		render_screen(cub_data, ry, i);
	}
	return (EXIT_SUCCESS);
}
