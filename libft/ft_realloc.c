/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:22:20 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/15 00:01:03 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t old_size, size_t new_size)
{
	void	*new_p;

	new_p = ft_calloc(1, new_size);
	if (!new_p)
		return (NULL);
	ft_memmove(new_p, p, old_size);
	free(p);
	return (new_p);
}
