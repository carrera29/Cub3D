/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollo <pollo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:28:58 by pollo             #+#    #+#             */
/*   Updated: 2023/05/31 18:19:04 by pollo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	t_map	map;

	if (argc == 2)
	{
		(ft_memset(&cub, 0, sizeof(cub)), ft_memset(&map, 0, sizeof(map)));
		(cub.map = &map, map.cub = &cub);
		if (ft_strncmp(ft_strchr(argv[1], '.'), ".cub\0", 5))
			return (error_msg(&cub, "File error"));
		if (get_map(&map, argv[1]))
			return (1);
	}
	return (0);
}
