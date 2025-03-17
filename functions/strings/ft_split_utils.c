/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:15:01 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/01 23:38:22 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '(' || c == ')' || c == '<' || c == '>');
}

int	process_quotes(const char *s, int *i, char quote)
{
	(*i)++;
	while (s[*i] && s[*i] != quote)
	{
		if (quote == '"' && s[*i] == '\\' && s[*i + 1])
			(*i)++;
		(*i)++;
	}
	if (!s[*i])
		return (-1);
	(*i)++;
	return (0);
}

int	check_assignment(const char *s)
{
	int	j;

	j = 0;
	while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
		j++;
	if (s[j] == '=')
		return (1);
	return (0);
}

int	get_operator_len(const char *s)
{
	if (!s[1])
		return (1);
	if ((s[0] == '&' && s[1] == '&') || (s[0] == '|' && s[1] == '|')
		|| (s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (2);
	return (1);
}

void	free_token_array(char **tokens, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(tokens[j]);
		j++;
	}
	free(tokens);
}
