/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/10/31 19:04:18 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug(void)
{
}

int	main(int argc, char **argv)
{
	t_cub	*cub_data;

	if (argc != 2)
		error(USAGE_ERROR, false);
	cub_data = initialization(argv[1]);
	start_game(cub_data);
	free_all(cub_data);
	return (EXIT_SUCCESS);
}
