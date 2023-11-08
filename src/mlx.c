/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:34 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/08 01:18:25 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	straight(t_cub *cub_data, double move_speed, char **map, char sign)
{
	int coor[2];

	if (sign == '+')
	{
		coor[X] = (int)cub_data->pos[X] + ((int)cub_data->dir[X] * (int)move_speed);
		coor[Y] = (int)cub_data->pos[Y] + ((int)cub_data->dir[Y] * (int)move_speed);
		if (map[coor[X]][(int)cub_data->pos[Y]] != WALL)
			cub_data->pos[X] += cub_data->dir[X] * cub_data->move_speed;
		if (map[(int)cub_data->pos[X]][coor[Y]] != WALL)
			cub_data->pos[Y] += cub_data->dir[Y] * cub_data->move_speed;
	}
	else
	{
		coor[X] = (int)cub_data->pos[X] - ((int)cub_data->dir[X] * (int)move_speed);
		coor[Y] = (int)cub_data->pos[Y] - ((int)cub_data->dir[Y] * (int)move_speed);
		if (map[coor[X]][(int)cub_data->pos[Y]] != WALL)
			cub_data->pos[X] -= cub_data->dir[X] * move_speed;
		if (map[(int)cub_data->pos[X]][coor[Y]] != WALL)
			cub_data->pos[Y] -= cub_data->dir[Y] * move_speed;
	}
}

void	rotate(t_cub *cub_data, double rot_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = cub_data->dir[X];
	cub_data->dir[Y] = (old_dirx * sin(rot_speed)) + (cub_data->dir[Y] * cos(rot_speed));
	cub_data->dir[X] = (old_dirx * cos(rot_speed)) - (cub_data->dir[Y] * sin(rot_speed));
	
	old_planex = cub_data->plane[X];
	cub_data->plane[X] = old_planex * cos(rot_speed) - (cub_data->plane[Y] * sin(rot_speed));
	cub_data->plane[Y] = old_planex * sin(rot_speed) + (cub_data->plane[Y] * cos(rot_speed));
}

void	key_hook(t_cub *cub_data, char **map)
{
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub_data->mlx);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_W))
		straight(cub_data, cub_data->move_speed, map, '+');
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_S))
		straight(cub_data, cub_data->move_speed, map, '-');
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_D))
		rotate(cub_data, (-1 * cub_data->rot_speed));
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_A))
		rotate(cub_data, cub_data->rot_speed);
}

void	loop_hook(void *param)
{
	t_cub	*cub_data;

	cub_data = param;
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
	cub_data->image[FLOOR_TEX] = mlx_new_image(cub_data->mlx, 128, 128);
	memset(cub_data->image[FLOOR_TEX]->pixels, map_data->floor_color,
		cub_data->image[FLOOR_TEX]->width
		* cub_data->image[FLOOR_TEX]->height * sizeof(int32_t));
	cub_data->image[CEILING_TEX] = mlx_new_image(cub_data->mlx, 128, 128);
	memset(cub_data->image[CEILING_TEX]->pixels, map_data->ceiling_color,
		cub_data->image[CEILING_TEX]->width
		* cub_data->image[CEILING_TEX]->height * sizeof(int32_t));
	i = -1;
	while (++i < SCREENWIDTH)
	{
		cub_data->line[i] = mlx_new_image(cub_data->mlx, 1, SCREENHEIGHT);
		mlx_image_to_window(cub_data->mlx, cub_data->line[i], i, 0);
	}
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
