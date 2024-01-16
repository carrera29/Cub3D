/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:45:24 by fmarin-p          #+#    #+#             */
/*   Updated: 2024/01/16 15:23:20 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*p;

	p = dst;
	if (!dst && !src)
		return (0);
	if (len == 0)
		return (dst);
	if (dst < src)
	{
		while (len--)
			*(char *)dst++ = *(char *)src++;
	}
	else
	{
		while (len--)
			*((char *)dst + len) = *((char *)src + len);
		*(char *)dst = *(char *)src;
	}
	return (p);
}
