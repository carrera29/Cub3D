/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:47:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/14 13:33:33 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_cub *cub_data, char **map, double dirX, double dirY)
{
	if (dirX > 0 && fmod(cub_data->pos[X], 1) > HITBOX
		&& map[(int)cub_data->pos[Y]][(int)cub_data->pos[X] + 1] != SPACE)
		dirX = 0;
	if (dirX < 0 && fmod(cub_data->pos[X], 1) < 1 - HITBOX
		&& map[(int)cub_data->pos[Y]][(int)cub_data->pos[X] - 1] != SPACE)
		dirX = 0;
	if (dirY > 0 && fmod(cub_data->pos[Y], 1) > HITBOX
		&& map[(int)cub_data->pos[Y] + 1][(int)cub_data->pos[X]] != SPACE)
		dirY = 0;
	if (dirY < 0 && fmod(cub_data->pos[Y], 1) < 1 - HITBOX
		&& map[(int)cub_data->pos[Y] - 1][(int)cub_data->pos[X]] != SPACE)
		dirY = 0;
	cub_data->pos[X] += dirX * cub_data->move_speed;
	cub_data->pos[Y] += dirY * cub_data->move_speed;
}

void	rotate(t_cub *cub_data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub_data->dir[X];
	old_plane_x = cub_data->plane[X];
	cub_data->dir[X] = cub_data->dir[X] * cos(rot_speed)
		- cub_data->dir[Y] * sin(rot_speed);
	cub_data->dir[Y] = old_dir_x * sin(rot_speed)
		+ cub_data->dir[Y] * cos(rot_speed);
	cub_data->plane[X] = cub_data->plane[X] * cos(rot_speed)
		- cub_data->plane[Y] * sin(rot_speed);
	cub_data->plane[Y] = old_plane_x * sin(rot_speed)
		+ cub_data->plane[Y] * cos(rot_speed);
}
