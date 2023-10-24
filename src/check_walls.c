/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:02:39 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/23 15:05:17 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid(bool **visited, int row, int col, int *size, char **map)
{
	if (visited[row][col] || row < 0 || col < 0
		|| row > size[HEIGHT || col > size[WIDTH]])
		return (false);
	return (true);
}

bool	**init_aux_map(int width, int height)
{
	bool	**aux_map;
	int		i;

	aux_map = ft_calloc(height + 1, sizeof(char *));
	i = -1;
	while (i < height)
		aux_map[i] = ft_calloc(width + 1, sizeof(char));
	return (aux_map);
}

int	check_walls(char **map, int *size)
{
	t_list	*stack;
	bool	**aux_map;

	stack = ft_lstnew(ft_calloc(2, sizeof(int)));
	aux_map = init_aux_map(size[WIDTH], size[HEIGHT]);
	while (stack)
	{
		stack = stack->next;
	}
	return (true);
}
