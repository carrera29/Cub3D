/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:56:28 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/09 15:39:07 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(int j, uint8_t *pixels, uint32_t width, int screen_pos)
{
	int	pixel;

	pixel = pixels[j * (width * 4) + (screen_pos % (width * 4))] << 24
		| pixels[j * (width * 4) + (screen_pos % (width * 4)) + 1] << 16
		| pixels[j * (width * 4) + (screen_pos % (width * 4)) + 2] << 8
		| pixels[j * (width * 4) + (screen_pos % (width * 4)) + 3];
	return (pixel);
}

int	render_wall(t_cub *cub_data, t_ray ry, int screen_pos, int i)
{
	mlx_texture_t	texture;
	double			resize_factor;
	double			j;
	int				pixel;

	texture = cub_data->xpm[ry.wall_texture]->texture;
	resize_factor = 1.0 * texture.height / (ry.end_draw - ry.start_draw);
	j = 0;
	while (++i < ry.end_draw)
	{
		pixel = get_pixel((int)j, texture.pixels, texture.width, screen_pos);
		mlx_put_pixel(cub_data->screen, screen_pos, i, pixel);
		j += resize_factor;
	}
	return (i);
}

int	print_screen(t_cub *cub_data, t_ray ry, int screen_pos)
{
	int	i;

	i = -1;
	while (++i < SCREENHEIGHT)
	{
		if (i < ry.start_draw)
			mlx_put_pixel(cub_data->screen, screen_pos, i,
				cub_data->map_data->ceiling_color);
		else if (i > ry.end_draw)
			mlx_put_pixel(cub_data->screen, screen_pos, i,
				cub_data->map_data->floor_color);
		else
			i = render_wall(cub_data, ry, screen_pos, --i);
	}
	return (EXIT_SUCCESS);
}

int	choose_texture(int side, double *pos, t_ray *ray)
{
	if (side == X)
	{
		if (ray->map[X] > pos[X])
			ray->wall_texture = WEST_TEX;
		else
			ray->wall_texture = WEST_TEX;
	}
	else if (side == Y)
	{
		if (ray->map[Y] > pos[Y])
			ray->wall_texture = SOUTH_TEX;
		else
			ray->wall_texture = NORTH_TEX;
	}
	return (EXIT_SUCCESS);
}
