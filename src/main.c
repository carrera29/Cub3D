/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/25 11:57:01 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug(void)
{
}

void	close_hook(void *param)
{
	t_cub	*cub_data;

	cub_data = param;
	mlx_delete_image(cub_data->mlx, cub_data->img);
	mlx_terminate(cub_data->mlx);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_hook(param);
}

int	screen_initialization(t_cub *cub_data, mlx_t *mlx)
{
	cub_data->img = mlx_new_image(mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!cub_data->img)
		return (EXIT_FAILURE);
	memset(cub_data->img->pixels, 0xFF,
		cub_data->img->width * cub_data->img->height * sizeof(int32_t));
	if (mlx_image_to_window(mlx, cub_data->img, 0, 0) < 0)
		return (EXIT_FAILURE);
	mlx_key_hook(mlx, key_hook, cub_data);
	mlx_close_hook(mlx, close_hook, cub_data);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub	*cub_data;

	debug();
	if (argc != 2)
		error(USAGE_ERROR, false);
	cub_data = initialization(argv[1]);
	cub_data->mlx = mlx_init(SCREENWIDTH, SCREENHEIGHT, argv[0] + 2, true);
	if (!cub_data->mlx)
		(free_all(cub_data), error(MLXINIT_ERROR, false));
	screen_initialization(cub_data, cub_data->mlx);
	free_all(cub_data);
	exit(EXIT_SUCCESS);
}
