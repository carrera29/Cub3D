/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:16:05 by pollo             #+#    #+#             */
/*   Updated: 2023/06/02 10:35:59 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_vectors(t_map *map, double x, double y)
{
	double  old_x;
	double  old_y;
	double  cos_angle;
	double  sin_angle;
	
	(old_x = x, old_y = y);
	(cos_angle = cos(map->angle), sin_angle = sin(map->angle));
	x = (old_x * cos_angle) - (old_y * sin_angle);
	y = (old_x * sin_angle) + (old_y * cos_angle);
}

void	move_blaz(t_map *map, double x, double y)
{
	double  old_x;
	double  old_y;
	
	(old_x = x, old_y = y);
	x = old_x +  (map->dir_x * SPEED);
	y = old_y +  (map->dir_y * SPEED);
}