/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:56:28 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/09 21:40:02 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(int pixel_y, uint8_t *pixels, uint32_t width, int pixel_x)
{
	int	pixel;

	pixel = pixels[pixel_y * width + pixel_x] << 24
		| pixels[pixel_y * width + pixel_x + 1] << 16
		| pixels[pixel_y * width + pixel_x + 2] << 8
		| pixels[pixel_y * width + pixel_x + 3];
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

int	render_wall(t_cub *cub_data, t_ray ry, int screen_x, int i)
{
	mlx_texture_t	texture;
	double			resize_factor;
	double			pixel_y;
	int				pixel_x;

	texture = cub_data->xpm[ry.wall_texture]->texture;
	pixel_x = get_texture_pos(cub_data, ry, texture.width);
	resize_factor = 1.0 * texture.height / ry.line_height;
	pixel_y = 0;
	if (ry.line_height > SCREENHEIGHT)
		pixel_y += (ry.line_height - SCREENHEIGHT) / 2 * resize_factor;
	while (++i <= ry.end_draw)
	{
		mlx_put_pixel(cub_data->screen, screen_x, i, get_pixel((int)pixel_y,
				texture.pixels, texture.width * texture.bytes_per_pixel,
				pixel_x * texture.bytes_per_pixel));
		pixel_y += resize_factor;
	}
	return (i);
}

int	render_screen(t_cub *cub_data, t_ray ry, int screen_x)
{
	int	i;

	i = -1;
	while (++i < SCREENHEIGHT)
	{
		mlx_put_pixel(cub_data->screen, screen_x,
			i, cub_data->map_data->floor_color);
		if (i < SCREENHEIGHT / 2)
			mlx_put_pixel(cub_data->screen, screen_x, i,
				cub_data->map_data->ceiling_color);
	}
	i = ry.start_draw - 1;
	while (++i < ry.end_draw)
		i = render_wall(cub_data, ry, screen_x, --i);
	return (EXIT_SUCCESS);
}

int	select_texture(t_ray *ray, double *pos)
{
	if (ray->side == X)
	{
		if (ray->ray_pos[X] > pos[X])
			ray->wall_texture = EAST_TEX;
		else
			ray->wall_texture = WEST_TEX;
	}
	else if (ray->side == Y)
	{
		if (ray->ray_pos[Y] > pos[Y])
			ray->wall_texture = NORTH_TEX;
		else
			ray->wall_texture = SOUTH_TEX;
	}
	return (EXIT_SUCCESS);
}
