/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:43:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/24 17:25:44 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_door(int door_trigger, double *door_state,
	double door_speed, char *map_char)
{
	if (door_trigger && *door_state == WAIT_DOOR)
		*door_state = OPENING_DOOR;
	if (*door_state >= OPENING_DOOR)
		*door_state += door_speed;
	if (*door_state >= OPEN_DOOR && door_trigger)
		*door_state = OPEN_DOOR;
	if (*door_state >= CLOSING_DOOR)
		*door_state = WAIT_DOOR;
	*map_char = DOOR;
	if (*door_state == OPEN_DOOR)
		*map_char = OP_DOOR;
	printf("door_state = %.2f\n", *door_state);
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
			if (cub_data->map_data->map[it[Y]][it[X]] == DOOR)
				check_door(door_trigger[it[Y]][it[X]],
					&door_state[it[Y]][it[X]], cub_data->door_speed,
					&cub_data->map_data->map[it[Y]][it[X]]);
	}
	return (EXIT_SUCCESS);
}

void	door_animation(t_cub *cub_data, double *pos, char **map)
{
	int	door_trigger[1024][1024];

	ft_memset(door_trigger, 0, sizeof(door_trigger));
	if (fmod(cub_data->pos[X], 1) > HITBOX
		&& (map[(int)pos[Y]][(int)pos[X] + 1] == DOOR
		|| map[(int)pos[Y]][(int)pos[X] + 1] == OP_DOOR))
		door_trigger[(int)pos[Y]][(int)pos[X] + 1] = true;
	if (fmod(cub_data->pos[X], 1) < 1 - HITBOX
		&& (map[(int)pos[Y]][(int)pos[X] - 1] == DOOR
		|| map[(int)pos[Y]][(int)pos[X] - 1] == OP_DOOR))
		door_trigger[(int)pos[Y]][(int)pos[X] - 1] = true;
	if (fmod(cub_data->pos[Y], 1) > HITBOX
		&& (map[(int)pos[Y] + 1][(int)pos[X]] == DOOR
		|| map[(int)pos[Y] + 1][(int)pos[X]] == OP_DOOR))
		door_trigger[(int)pos[Y] + 1][(int)pos[X]] = true;
	if (fmod(cub_data->pos[Y], 1) < 1 - HITBOX
		&& (map[(int)pos[Y] - 1][(int)pos[X]] == DOOR
		|| map[(int)pos[Y] - 1][(int)pos[X]] == OP_DOOR))
		door_trigger[(int)pos[Y] - 1][(int)pos[X]] = true;
	check_doors_state(cub_data, door_trigger, cub_data->map_data->size);
}
