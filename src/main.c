/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/25 12:22:36 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug(void)
{
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		(void) param;
}

int	screen_initialization(t_cub *cub_data, mlx_t *mlx)
{
	mlx_key_hook(mlx, key_hook, cub_data);
	mlx_loop(mlx);
	mlx_terminate(cub_data->mlx);
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
	return (EXIT_SUCCESS);
}
