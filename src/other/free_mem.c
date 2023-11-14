/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/14 13:40:01 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_if_def(void *data)
{
	if (!data)
		return ;
	free(data);
}

void	free_all(t_cub *cub_data)
{
	int	i;

	if (!cub_data->map_data)
	{
		free(cub_data);
		return ;
	}
	if (cub_data->map_data->map)
		ft_freedp(cub_data->map_data->map);
	i = -1;
	while (++i <= SPRITE_TEX)
	{
		free_if_def(cub_data->map_data->texture_path[i]);
		mlx_delete_xpm42(cub_data->xpm[i]);
	}
	mlx_delete_xpm42(cub_data->xpm[DOOR_TEX]);
	mlx_delete_xpm42(cub_data->xpm[DOORJAM_TEX]);
	free(cub_data->map_data);
	free(cub_data);
}
