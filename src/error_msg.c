/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:35:28 by pollo             #+#    #+#             */
/*   Updated: 2023/05/31 18:31:06 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_program(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->map->map)
		while(cub->map->map[i])
			(free(cub->map->map[i]), i++);
}

int	error_msg(t_cub *cub, char *msg)
{
	write (1, "Error\n", 7);
	write (1, msg, ft_strlen(msg));
	write (1, "\n", 1);
	return (end_program(cub), 1);
}

int	check_perror(int code, char *name)
{
	if (code == -1)
		perror(name);
	return (code);
}