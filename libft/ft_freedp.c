/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freedp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:56:56 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/11/24 19:39:41 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freedp(void **dp, int rows)
{
	int	i;

	i = -1;
	if (!rows)
	{
		while (dp[++i])
			free(dp[i]);
	}
	else
	{
		while (++i < rows)
			free(dp[i]);
	}
	free(dp);
}
