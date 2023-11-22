/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:56:28 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/22 23:21:49 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel(uint8_t *pixels, int pixel_y, uint32_t width, int pixel_x)
{
	int	pixel;
	int	index;

	index = pixel_y * width + pixel_x;
	pixel = pixels[index] << 24
		| pixels[index + 1] << 16
		| pixels[index + 2] << 8
		| pixels[index + 3];
	return (pixel);
}

double	get_texture_pos(t_cub *cub_data, t_ray ry)
{
	double	wall_x;

	wall_x = cub_data->pos[ry.side ^ 1]
		+ ry.perp_wall_dist * ry.raydir[ry.side ^ 1];
	wall_x = fmod(wall_x, 1);
	return (wall_x);
}

int	render_wall(t_cub *cub_data, t_ray ry, int screen_x)
{
	mlx_texture_t	texture;
	double			resize_factor;
	double			pixel_y;
	int				pixel_x;

	texture = cub_data->xpm[ry.wall_texture]->texture;
	resize_factor = 1.0 * texture.height / (ry.line_height + 1);
	pixel_x = get_texture_pos(cub_data, ry) * texture.width;
	pixel_y = 0;
	if (ry.line_height > SCREENHEIGHT)
		pixel_y = (ry.line_height - SCREENHEIGHT) / 2 * resize_factor;
	--ry.start_draw;
	while (++ry.start_draw <= ry.end_draw)
	{
		mlx_put_pixel(cub_data->screen, screen_x, ry.start_draw,
			get_pixel(texture.pixels, (int)pixel_y, texture.width
				* texture.bytes_per_pixel, pixel_x * texture.bytes_per_pixel));
		pixel_y += resize_factor;
	}
	return (EXIT_SUCCESS);
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
	render_wall(cub_data, ry, screen_x);
	return (EXIT_SUCCESS);
}

int	select_texture(t_ray *ray, double *pos, char **map)
{
	const int	table[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

	if (ray->wall_texture)
		return (EXIT_FAILURE);
	if (ray->side == X)
	{
		ray->wall_texture = EAST_TEX;
		if (ray->ray_pos[X] > pos[X])
			ray->wall_texture = WEST_TEX;
	}
	else if (ray->side == Y)
	{
		ray->wall_texture = NORTH_TEX;
		if (ray->ray_pos[Y] > pos[Y])
			ray->wall_texture = SOUTH_TEX;
	}
	if (map[(int)pos[Y] + table[ray->wall_texture][Y]]
		[(int)pos[X] + table[ray->wall_texture][X]] == DOOR
		&& map[ray->ray_pos[Y]][ray->ray_pos[X]] == DOOR)
		ray->wall_texture = DOORJAM_TEX;
	return (EXIT_SUCCESS);
}
