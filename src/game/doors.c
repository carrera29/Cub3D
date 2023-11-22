/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:43:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/22 20:14:23 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_door(t_cub *cub_data, int door_trigger[][1024],
	double door_state[][1024], int *it)
{
	if (door_trigger[it[Y]][it[X]] == false && door_state[it[Y]][it[X]])
				door_state[it[Y]][it[X]] -= cub_data->door_speed;
	else if (door_trigger[it[Y]][it[X]] == true
		|| door_state[it[Y]][it[X]] > false)
		door_state[it[Y]][it[X]] += cub_data->door_speed;
	if (door_state[it[Y]][it[X]] < false)
	{
		cub_data->map_data->map[it[Y]][it[X]] = DOOR;
		door_state[it[Y]][it[X]] = false;
	}
	else if (door_state[it[Y]][it[X]] >= true)
	{
		cub_data->map_data->map[it[Y]][it[X]] = SPACE;
		door_state[it[Y]][it[X]] = true;
	}
	return (EXIT_SUCCESS);
}

int	check_doors_state(t_cub *cub_data, int door_trigger[][1024], int *size)
{
	static double	door_state[1024][1024];
	int				it[2];

	it[Y] = -1;
	while (++it[Y] < size[HEIGHT])
	{
		it[X] = -1;
		while (++it[X] < size[WIDTH])
			check_door(cub_data, door_trigger, door_state, it);
	}
	return (EXIT_SUCCESS);
}

void	door_animation(t_cub *cub_data, double *pos, char **map)
{
	int	door_trigger[1024][1024];

	ft_memset(door_trigger, 0, sizeof(door_trigger));
	if (fmod(cub_data->pos[X], 1) > HITBOX
		&& map[(int)pos[Y]][(int)pos[X] + 1] == DOOR)
		door_trigger[(int)pos[Y]][(int)pos[X] + 1] = true;
	if (fmod(cub_data->pos[X], 1) < 1 - HITBOX
		&& map[(int)pos[Y]][(int)pos[X] - 1] == DOOR)
		door_trigger[(int)pos[Y]][(int)pos[X] - 1] = true;
	if (fmod(cub_data->pos[Y], 1) > HITBOX
		&& map[(int)pos[Y] + 1][(int)pos[X]] == DOOR)
		door_trigger[(int)pos[Y] + 1][(int)pos[X]] = true;
	if (fmod(cub_data->pos[Y], 1) < 1 - HITBOX
		&& map[(int)pos[Y] - 1][(int)pos[X]] == DOOR)
		door_trigger[(int)pos[Y] - 1][(int)pos[X]] = true;
	check_doors_state(cub_data, door_trigger, cub_data->map_data->size);
}
