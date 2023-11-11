/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:34 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/11 13:45:31 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_screen_center(int *center, mlx_t *mlx)
{
	int32_t	window_x;
	int32_t	window_y;

	mlx_get_window_pos(mlx, &window_x, &window_y);
	center[X] = window_x + (SCREENWIDTH / 2);
	center[Y] = window_y + (SCREENHEIGHT / 2);
	return (EXIT_SUCCESS);
}

int	load_images(t_cub *cub_data, t_map *map_data)
{
	int	i;

	i = -1;
	while (++i <= SPRITE_TEX)
		cub_data->xpm[i] = mlx_load_xpm42(map_data->texture_path[i]);
	cub_data->screen = mlx_new_image(cub_data->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx_image_to_window(cub_data->mlx, cub_data->screen, 0, 0);
	render_minimap_hub(cub_data->mlx);
	return (EXIT_SUCCESS);
}

int	start_game(t_cub *cub_data)
{
	cub_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3D", true);
	if (!cub_data->mlx)
		(free_all(cub_data), error(MLXINIT_ERROR, false));
	load_images(cub_data, cub_data->map_data);
	get_screen_center(cub_data->center, cub_data->mlx);
	mlx_set_cursor_mode(cub_data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub_data->mlx, cub_data->center[X], cub_data->center[Y]);
	mlx_loop_hook(cub_data->mlx, loop_hook, cub_data);
	mlx_loop(cub_data->mlx);
	mlx_terminate(cub_data->mlx);
	return (EXIT_SUCCESS);
}
