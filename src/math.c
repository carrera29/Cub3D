/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:12:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/31 20:23:45 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initial_dir_vector(enum e_mapchar dir, double *vector)
{
	if (!dir)
		return ;
	if (dir == NORTH)
	{
		vector[X] = 0;
		vector[Y] = 1;
	}
	else if (dir == SOUTH)
	{
		vector[X] = 0;
		vector[Y] = -1;
	}
	else if (dir == WEST)
	{
		vector[X] = -1;
		vector[Y] = 0;
	}
	else if (dir == EAST)
	{
		vector[X] = 1;
		vector[Y] = 0;
	}
}
