/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:34 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/08 02:40:29 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_cub *cub_data, double move_speed, char **map, int dir)
{
	const double	table[4][2] = {{0.0, -move_speed}, {0.0, move_speed},
	{-move_speed, 0.0}, {move_speed, 0.0}};
	const int		grid_table[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

	if ((cub_data->pos[X] + table[dir][X] < HITBOX
		|| cub_data->pos[X] + table[dir][X] > (1 - HITBOX)
		|| cub_data->pos[Y] + table[dir][Y] < HITBOX
		|| cub_data->pos[Y] + table[dir][Y] > (1 - HITBOX))
		&& map[(int)cub_data->pos[Y] + grid_table[dir][Y]]
		[(int)cub_data->pos[X] + grid_table[dir][X]] == WALL)
		return ;
	cub_data->pos[X] += table[dir][X];
	cub_data->pos[Y] += table[dir][Y];
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

void	key_hook(t_cub *cub_data, char **map)
{
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub_data->mlx);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_W))
		move(cub_data, cub_data->move_speed, map, 0);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_A))
		move(cub_data, cub_data->move_speed, map, 3);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_D))
		move(cub_data, cub_data->move_speed, map, 2);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_S))
		move(cub_data, cub_data->move_speed, map, 1);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_RIGHT))
		rotate(cub_data, (-1 * cub_data->rot_speed));
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_LEFT))
		rotate(cub_data, cub_data->rot_speed);
}

void	loop_hook(void *param)
{
	t_cub	*cub_data;

	cub_data = param;
	cub_data->move_speed = cub_data->mlx->delta_time * 5.0;
	cub_data->rot_speed = cub_data->mlx->delta_time * 2.0;
	key_hook(cub_data, cub_data->map_data->map);
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
	cub_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3D", true);
	if (!cub_data->mlx)
		(free_all(cub_data), error(MLXINIT_ERROR, false));
	load_images(cub_data, cub_data->map_data);
	mlx_loop_hook(cub_data->mlx, loop_hook, cub_data);
	mlx_loop(cub_data->mlx);
	mlx_terminate(cub_data->mlx);
	return (EXIT_SUCCESS);
}
