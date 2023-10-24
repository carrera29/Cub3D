/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:17:14 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/24 16:17:41 by fmarin-p         ###   ########.fr       */
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
	if (cub_data->map_data)
	{
		if (cub_data->map_data->map)
			ft_freedp(cub_data->map_data->map);
		free_if_def(cub_data->map_data->north_texture);
		free_if_def(cub_data->map_data->south_texture);
		free_if_def(cub_data->map_data->west_texture);
		free_if_def(cub_data->map_data->east_texture);
		free(cub_data->map_data);
	}
	free(cub_data);
}