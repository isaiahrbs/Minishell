/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:45:38 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/05 17:46:42 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_me(char **output, int index)
{
	while (index >= 0)
		free(output[index--]);
	free (output);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			counter++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (counter);
}

static char	*add_words(int word_len, const char *s, char **strings, int j)
{
	int		i;

	i = 0;
	strings[j] = malloc(sizeof(char) * (word_len + 1));
	if (!strings[j])
	{
		free_me(strings, j);
		return (NULL);
	}
	while (i < word_len)
	{
		strings[j][i] = s[i];
		i++;
	}
	strings[j][i] = 0;
	return (strings[j]);
}

static int	count_letters(const char *s, char c, int *word_len)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	*word_len = i;
	return (i);
}

char	**real_split(const char *s, char c)
{
	int		i;
	int		j;
	int		word_len;
	char	**strings;

	i = 0;
	j = 0;
	strings = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strings)
		return (NULL);
	while (s[i])
	{
		word_len = 0;
		while (s[i] == c)
			i++;
		if (count_letters(&s[i], c, &word_len))
		{
			if (add_words(word_len, &s[i], strings, j) == NULL)
				return (NULL);
			j++;
		}
		i += word_len;
	}
	strings[j] = 0;
	return (strings);
}