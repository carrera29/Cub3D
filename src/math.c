/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:12:53 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/24 15:24:06 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*dir_vector(t_dir_vectors dir)
{
	int	*vector;

	if (!dir)
		return (NULL);
	vector = ft_calloc(2, sizeof(int));
	vector[X] = ((dir >> 2) & 1) | (((dir >> 3) & 1) * 0x7FFFFFFF << 1);
	vector[Y] = (dir & 1) | (((dir >> 1) & 1) * 0x7FFFFFFF << 1);
	return (vector);
}
