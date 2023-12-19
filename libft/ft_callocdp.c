/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_callocdp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:35:59 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/01 21:44:40 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_callocdp(size_t row, size_t col, size_t size)
{
	void	**p;
	int		i;

	p = ft_calloc(row, sizeof(void *));
	if (!p)
		return (NULL);
	i = -1;
	while (++i < (int)row)
	{
		p[i] = ft_calloc(col, size);
		if (!p[i])
			return (NULL);
	}
	return (p);
}
