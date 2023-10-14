/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:22:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/15 01:02:51 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t old_count,
		size_t new_count, size_t type_size)
{
	void	*new_p;

	new_p = ft_calloc(1, new_count * type_size);
	if (!new_p)
		return (NULL);
	ft_memmove(new_p, p, old_count * type_size);
	free(p);
	return (new_p);
}
