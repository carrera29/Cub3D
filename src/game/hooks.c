/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:13:03 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/11 20:08:14 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(t_cub *cub_data, mlx_t *mlx, double rot_speed)
{
	int32_t	delta;
	int32_t	y_pos;

	mlx_get_mouse_pos(mlx, &delta, &y_pos);
	if (delta > cub_data->center[X])
		rotate(cub_data, -(rot_speed + fabs((double)delta - cub_data->center[X])
				* MOUSE_ACC));
	else if (delta < cub_data->center[X])
		rotate(cub_data, rot_speed + fabs((double)delta - cub_data->center[X])
			* MOUSE_ACC);
	mlx_set_mouse_pos(cub_data->mlx, cub_data->center[X], cub_data->center[Y]);
	return (EXIT_SUCCESS);
}

void	key_hook(t_cub *cub_data, char **map)
{
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub_data->mlx);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_W))
		move(cub_data, map, cub_data->dir[X], cub_data->dir[Y]);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_A))
		move(cub_data, map, -cub_data->dir[Y], cub_data->dir[X]);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_D))
		move(cub_data, map, cub_data->dir[Y], -cub_data->dir[X]);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_S))
		move(cub_data, map, -cub_data->dir[X], -cub_data->dir[Y]);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_RIGHT))
		rotate(cub_data, -cub_data->rot_speed);
	else if (mlx_is_key_down(cub_data->mlx, MLX_KEY_LEFT))
		rotate(cub_data, cub_data->rot_speed);
}

void	loop_hook(void *param)
{
	t_cub	*cub_data;

	cub_data = param;
	cub_data->move_speed = cub_data->mlx->delta_time * MOVE_SPEED;
	cub_data->rot_speed = cub_data->mlx->delta_time * ROTATION_SPEED;
	key_hook(cub_data, cub_data->map_data->map);
	mouse_hook(cub_data, cub_data->mlx, cub_data->rot_speed);
	raycasting(cub_data);
	render_minimap(cub_data, cub_data->mlx, cub_data->map_data);
}
