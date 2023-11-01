/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/11/01 23:36:16 by fmarin-p         ###   ########.fr       */
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
		error(USAGE_ERROR, false);
	cub_data = initialization(argv[1]);
	start_game(cub_data);
	free_all(cub_data);
	return (EXIT_SUCCESS);
}
