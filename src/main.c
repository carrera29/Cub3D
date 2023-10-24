/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/24 15:29:44 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug(void)
{
}

int	main(int argc, char **argv)
{
	t_cub	*cub_data;

	debug();
	if (argc != 2)
		return (printf("Usage: ./cub3D [.cub extension map]\n"), EXIT_FAILURE);
	cub_data = initialization(argv[1]);
	print_data(cub_data);
	exit(EXIT_SUCCESS);
}
