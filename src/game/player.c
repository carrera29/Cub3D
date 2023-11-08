/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:47:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/08 10:48:16 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_cub *cub_data, char **map, double dirX, double dirY)
{
	(void) map;
	// if ((cub_data->pos[X] + cub_data->move_speed < HITBOX
	// 		|| cub_data->pos[X] + cub_data->move_speed > (1 - HITBOX)
	// 		|| cub_data->pos[Y] + cub_data->move_speed < HITBOX
	// 		|| cub_data->pos[Y] + cub_data->move_speed > (1 - HITBOX)))
	// 	return ;
	cub_data->pos[X] += dirX * cub_data->move_speed;
	cub_data->pos[Y] += dirY * cub_data->move_speed;
}

void	rotate(t_cub *cub_data, double rot_speed)
{
	cub_data->dir[Y] = (cub_data->dir[X] * sin(rot_speed))
		+ (cub_data->dir[Y] * cos(rot_speed));
	cub_data->dir[X] = (cub_data->dir[X] * cos(rot_speed))
		- (cub_data->dir[Y] * sin(rot_speed));
	cub_data->plane[X] = cub_data->plane[X] * cos(rot_speed)
		- (cub_data->plane[Y] * sin(rot_speed));
	cub_data->plane[Y] = cub_data->plane[X] * sin(rot_speed)
		+ (cub_data->plane[Y] * cos(rot_speed));
}
