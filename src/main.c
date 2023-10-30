/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/30 21:01:26 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug(void)
{
}

void	loop_hook(void *param)
{
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

int	load_images(t_cub *cub_data, t_map *map_data)
{
	int	i;

	i = -1;
	while (++i <= EAST_TEX)
	{
		cub_data->texture[i] = mlx_load_xpm42(map_data->texture_path[i]);
		cub_data->image[i] = mlx_texture_to_image(
				cub_data->mlx, &cub_data->texture[i]->texture);
		mlx_delete_xpm42(cub_data->texture[i]);
	}
	return (EXIT_SUCCESS);
}

int	start_game(t_cub *cub_data, mlx_t *mlx)
{
	mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, "cub3D", true);
	if (!mlx)
		(free_all(cub_data), error(MLXINIT_ERROR, false));
	load_images(cub_data, cub_data->map_data);
	mlx_loop_hook(mlx, loop_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub	*cub_data;

	debug();
	if (argc != 2)
		error(USAGE_ERROR, false);
	cub_data = initialization(argv[1]);
	start_game(cub_data, cub_data->mlx);
	free_all(cub_data);
	return (EXIT_SUCCESS);
}
