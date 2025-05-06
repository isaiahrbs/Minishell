/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:22:16 by dimatayi          #+#    #+#             */
/*   Updated: 2025/05/06 15:58:09 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_tokens_in_str(const char *s)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace((unsigned char)s[i]))
			i++;
		if (!s[i])
			break ;
		len = get_token_length(&s[i]);
		if (len < 0)
			return (-1);
		count++;
		i += len;
	}
	return (count);
}

static char	*extract_token_str(const char *s, int len)
{
	char	*token;
	int		i;

	token = malloc(len + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = s[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

static int	fill_token_array(char **tokens, char *s)
{
	int	i;
	int	token_idx;
	int	len;

	i = 0;
	token_idx = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace((unsigned char)s[i]))
			i++;
		if (!s[i])
			break ;
		len = get_token_length(&s[i]);
		if (len < 0)
			return (-1);
		tokens[token_idx] = extract_token_str(&s[i], len);
		if (!tokens[token_idx])
			return (-1);
		token_idx++;
		i += len;
	}
	tokens[token_idx] = NULL;
	return (0);
}

char	**metachar_split(char *s)
{
	int		token_count;
	char	**tokens;
	int		status;

	token_count = count_tokens_in_str(s);
	if (token_count < 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	status = fill_token_array(tokens, s);
	if (status == -1)
	{
		free_token_array(tokens, token_count);
		return (NULL);
	}
	return (tokens);
}
