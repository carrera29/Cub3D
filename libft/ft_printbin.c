/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:46:00 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/24 14:49:21 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printbin(int n)
{
	int	i;

	i = 0;
	while (++i <= 32)
	{
		if ((n >> (32 - i)) & 1)
			ft_putchar_fd('1', STDOUT_FILENO);
		else
			ft_putchar_fd('0', STDOUT_FILENO);
		if (i % 8 == 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
