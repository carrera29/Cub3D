/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:43:55 by fmarin-p          #+#    #+#             */
/*   Updated: 2023/10/04 13:52:20 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_delimiter(char const *str, int delimiter)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
		{
			while (str[i] != delimiter && str[i])
				i++;
			count++;
		}
		if (!str[i])
			break ;
		i++;
	}
	return (count);
}

size_t	count_str(const char *str, int i, int delimiter)
{
	int	size;

	size = 0;
	while (str[i] != delimiter && str[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	*allocate_substring(const char *str, int *i, int delimiter)
{
	char	*substr;
	size_t	size;
	int		index;

	size = count_str(str, *i, delimiter) + 1;
	substr = ft_calloc(size, sizeof(char));
	index = 0;
	while (--size)
		substr[index++] = str[(*i)++];
	return (substr);
}

int	allocate_strings(char **split, char const *s, char c)
{
	int		i;
	int		index;

	i = -1;
	index = 0;
	while (s[++i])
	{
		while (s[i] != c && s[i])
			split[index++] = allocate_substring(s, &i, c);
		if (!s[i])
			break ;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = ft_calloc(count_delimiter(s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	allocate_strings(split, s, c);
	return (split);
}
