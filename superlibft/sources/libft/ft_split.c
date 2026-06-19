/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:07:25 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/23 17:00:20 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	safe_malloc(char **array, int position, int buffer)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	array[position] = malloc(buffer);
	if (!array[position])
	{
		while (i < position)
		{
			free(array[i]);
			i++;
		}
		free(array);
		return (1);
	}
	return (0);
}

int	fill(char **array, char const *s, char c)
{
	int	i;
	int	len;
	int	word_index;

	i = 0;
	word_index = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i + len] && s[i + len] != c)
			len++;
		if (len > 0)
		{
			if (safe_malloc(array, word_index, len + 1))
				return (1);
			ft_strlcpy(array[word_index++], &s[i], len + 1);
		}
		i += len;
	}
	return (0);
}

int	count_words(char const *s, char c)
{
	int	words;
	int	inside_word;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		inside_word = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (!inside_word)
			{
				words++;
				inside_word = 1;
			}
			i++;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**array;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array[words] = NULL;
	if (fill(array, s, c))
	{
		free(array);
		return (NULL);
	}
	return (array);
}

/* int	main(int ac, char **av)
{
	char	**split = ft_split(av[1], av[2][0]);
	int	i = 0;

	if (ac < 3)
		return (1);
	while (split[i])
	{	
		printf("Mot : %d --> %s\n", i, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
} */
