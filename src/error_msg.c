/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:35:28 by pollo             #+#    #+#             */
/*   Updated: 2023/10/07 18:30:25 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	end_program(t_cub *cub)
{
}

int	error_msg(t_map *map, char *msg)
{
	ft_putstr_fd("[ERROR]\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (end_program(map), 1);
}

int	check_perror(int code, char *name)
{
	if (code == -1)
		perror(name);
	return (code);
}