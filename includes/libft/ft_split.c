/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goncalo1021pt <goncalo1021pt@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:16:31 by gfontao-          #+#    #+#             */
/*   Updated: 2024/03/28 15:12:00 by goncalo1021      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char c)
{
	int	ctd;
	int	total;

	ctd = 0;
	total = 0;
	while (str[ctd])
	{
		while (str[ctd] && str[ctd] == c)
			ctd++;
		if (str[ctd])
			total++;
		while (str[ctd] && str[ctd] != c)
			ctd++;
	}
	return (total);
}

static char	*word_aloc(const char *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = -1;
	word_len = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	word = (char *)malloc(word_len + 1);
	if (!word)
		return (NULL);
	while (++ctd < word_len)
		word[ctd] = str[ctd];
	word[ctd] = '\0';
	return (word);
}

static void	*free_str(char **out, int ctd)
{
	while (ctd >= 0)
		free(out[ctd--]);
	free(out);
	return (NULL);
}

void	ft_free_split(char **split)
{
	int	ctd;

	ctd = 0;
	while (split[ctd])
		free(split[ctd++]);
	free(split);
	split = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		ctd;

	ctd = 0;
	out = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			out[ctd] = word_aloc(s, c);
			if (!out[ctd++])
				return (free_str(out, ctd));
		}
		while (*s && *s != c)
			s++;
	}
	out[ctd] = 0;
	return (out);
}
