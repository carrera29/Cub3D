/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:56:28 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/09 20:00:31 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(int j, uint8_t *pixels, uint32_t width, int texture_pos)
{
	int	pixel;

	pixel = pixels[j * width + texture_pos] << 24
		| pixels[j * width + texture_pos + 1] << 16
		| pixels[j * width + texture_pos + 2] << 8
		| pixels[j * width + texture_pos + 3];
	return (pixel);
}

int	get_texture_pos(t_cub *cub_data, t_ray ry, int32_t width)
{
	double	wall_x;

	wall_x = cub_data->pos[X] + ry.perp_wall_dist * ry.raydir[X];
	if (ry.side == X)
		wall_x = cub_data->pos[Y] + ry.perp_wall_dist * ry.raydir[Y];
	wall_x = fmod(wall_x, 1);
	return (wall_x * width);
}

int	render_wall(t_cub *cub_data, t_ray ry, int screen_pos, int i)
{
	mlx_texture_t	texture;
	double			resize_factor;
	double			j;
	int				texture_pos;

	texture = cub_data->xpm[ry.wall_texture]->texture;
	texture_pos = get_texture_pos(cub_data, ry, texture.width);
	resize_factor = 1.0 * texture.height / (ry.end_draw - ry.start_draw);
	j = 0;
	while (++i <= ry.end_draw)
	{
		mlx_put_pixel(cub_data->screen, screen_pos, i, get_pixel((int)j,
				texture.pixels, texture.width * texture.bytes_per_pixel,
				texture_pos * texture.bytes_per_pixel));
		j += resize_factor;
	}
	return (i);
}

int	render_screen(t_cub *cub_data, t_ray ry, int screen_pos)
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

int	select_texture(t_ray *ray, double *pos)
{
	if (ray->side == X)
	{
		if (ray->ray_pos[X] > pos[X])
			ray->wall_texture = WEST_TEX;
		else
			ray->wall_texture = WEST_TEX;
	}
	else if (ray->side == Y)
	{
		if (ray->ray_pos[Y] > pos[Y])
			ray->wall_texture = SOUTH_TEX;
		else
			ray->wall_texture = NORTH_TEX;
	}
	return (EXIT_SUCCESS);
}
