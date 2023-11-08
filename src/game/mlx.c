/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:34 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/08 16:50:23 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(t_cub *cub_data, mlx_t *mlx, double rot_speed)
{
	int32_t	delta;
	int32_t	y_pos;

	mlx_get_mouse_pos(mlx, &delta, &y_pos);
	if (delta > SCREENWIDTH / 2)
		rotate(cub_data, -(rot_speed + fabs((double)delta - SCREENWIDTH / 2)
				* MOUSE_ACC));
	else if (delta < SCREENWIDTH / 2)
		rotate(cub_data, rot_speed + fabs((double)delta - SCREENWIDTH / 2)
			* MOUSE_ACC);
	mlx_set_mouse_pos(mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
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
}

int	load_images(t_cub *cub_data, t_map *map_data)
{
	int	i;

	i = -1;
	while (++i <= SPRITE_TEX)
	{
		cub_data->texture[i] = mlx_load_xpm42(map_data->texture_path[i]);
		cub_data->image[i] = mlx_texture_to_image(cub_data->mlx,
				&cub_data->texture[i]->texture);
		mlx_delete_xpm42(cub_data->texture[i]);
	}
	cub_data->view = mlx_new_image(cub_data->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx_image_to_window(cub_data->mlx, cub_data->view, 0, 0);
	return (EXIT_SUCCESS);
}

int	start_game(t_cub *cub_data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cub_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3D", true);
	if (!cub_data->mlx)
		(free_all(cub_data), error(MLXINIT_ERROR, false));
	load_images(cub_data, cub_data->map_data);
	mlx_set_cursor_mode(cub_data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub_data->mlx, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_loop_hook(cub_data->mlx, loop_hook, cub_data);
	mlx_loop(cub_data->mlx);
	mlx_terminate(cub_data->mlx);
	return (EXIT_SUCCESS);
}
