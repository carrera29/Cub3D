/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:45:34 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/01 20:48:09 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(t_cub *cub_data)
{
	double moveSpeed;
	double pos[2];
	double dir[2];
	double oldDir[2];


	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub_data->mlx);
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_W))
	{
		if (!(cub_data->map_data->map[(int)pos[X] + (int)dir[X] * moveSpeed][(int)pos[Y]]))
			pos[X] += dir[X] * moveSpeed;
		if (!(cub_data->map_data->map[(int)pos[X]][(int)pos[Y] + (int)dir[Y] * moveSpeed]))
			pos[Y] += dir[Y] * moveSpeed;
	}
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_S))
	{}	
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_A))
	{}
	if (mlx_is_key_down(cub_data->mlx, MLX_KEY_D))
	{}
}

int	step_by_step(t_cub *cub_data)
{
}

int	raycasting(t_cub *cub_data)
{
	int i;
	int step[2];
	int map[2];
	double camaraX;
	double raydir[2];
	double sideDist[2];
	double deltaDist[2];
	double plane[2];

	i = -1;
	while (++i < SCREENWIDTH)
	{
		//raycating
		plane[X] = 0, plane[Y] = 0.66;
		camaraX = (i * 2) / (SCREENHEIGHT - 1);
		raydir[X] = cub_data->dir[X] + plane[X] * camaraX;
		raydir[Y] = cub_data->dir[Y] + plane[Y] * camaraX;

		// calculo deltaDist y sideDist
		if (raydir[X] == 0) 
			deltaDist[X] = fabs(1 / 1e30);
		else
			deltaDist[X] = fabs(1 / raydir[X]);
		if (raydir[X] == 0)
			deltaDist[Y] = fabs(1 / raydir[Y]);
		else
			deltaDist[Y] = fabs(1 / raydir[Y]);
		
		map[X] = (int)cub_data->pos[X];
		map[Y] = (int)cub_data->pos[Y];
		if (raydir[X] < 0)
			(step[X] = -1, sideDist[X] = (cub_data->pos[X] - map[X]) * deltaDist[X]);
		else
			(step[X] = 1, sideDist[X] = (map[X] + 1 - cub_data->pos[X]) * deltaDist[X]);
		if (raydir[Y] < 0)
			(step[Y] = -1, sideDist[Y] = (cub_data->pos[Y] - map[Y]) * deltaDist[Y]);
		else
			(step[Y] = 1, sideDist[Y] = (map[Y] + 1 - cub_data->pos[Y]) * deltaDist[Y]);

		// step by step
		int hit;
		double perpWallDist;
		hit = 0; 
		while (hit == 0)
		{
			if (sideDist[X] < sideDist[Y])
			{
				sideDist[X] += deltaDist[X];
				map[X] += step[X];
				perpWallDist = (sideDist[X] - deltaDist[X]);
			}
			else
			{
				sideDist[Y] += deltaDist[Y];
				map[Y] += step[Y];
				perpWallDist = (sideDist[Y] - deltaDist[Y]);
			}
			if (cub_data->map_data->map[map[X]][map[Y]] < 0)
				hit = 1;
		}
	}
}

void	loop_hook(void *param)
{
	t_cub	*cub_data;

	cub_data = param;
	raycasting(cub_data);
	key_hook(cub_data);
}

int	load_images(t_cub *cub_data, t_map *map_data)
{
	int	i;

	i = -1;
	while (++i <= EAST_TEX)
	{
		cub_data->texture[i] = mlx_load_xpm42(map_data->texture_path[i]);
		cub_data->image[i] = mlx_texture_to_image(cub_data->mlx,
				&cub_data->texture[i]->texture);
		mlx_delete_xpm42(cub_data->texture[i]);
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
