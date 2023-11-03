/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:34 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/03 15:14:24 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(t_cub *cub_data)
{
	// double	move_speed;
	// double	pos[2];
	// double	dir[2];
	//double	old_dir[2];

	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub_data->mlx);
	// if (mlx_is_key_down(cub_data->mlx, MLX_KEY_W))
	// {
	// 	if (!(cub_data->map_data->map[(int)pos[X] + (int)dir[X] * (int)move_speed][(int)pos[Y]]))
	// 		pos[X] += dir[X] * move_speed;
	// 	if (!(cub_data->map_data->map[(int)pos[X]][(int)pos[Y] + (int)dir[Y] * (int)move_speed]))
	// 		pos[Y] += dir[Y] * move_speed;
	// }
	// if (mlx_is_key_down(cub_data->mlx, MLX_KEY_S))
	// {

	// }
	// if (mlx_is_key_down(cub_data->mlx, MLX_KEY_A))
	// {

	// }
	// if (mlx_is_key_down(cub_data->mlx, MLX_KEY_D))
	// {

	// }
}

void	loop_hook(void *param)
{
	t_cub	*cub_data;

	cub_data = param;
	key_hook(cub_data);
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
