/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:53:11 by dimatayi          #+#    #+#             */
/*   Updated: 2025/05/06 15:53:22 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_quotes(const char *s, int *i)
{
	char	quote;
	int		start;

	start = *i;
	quote = s[(*i)++];
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] != quote)
		return (-1);
	(*i)++;
	return (*i - start);
}

int	handle_word(const char *s, int is_assign)
{
	int		i;
	int		tmp;

	i = 0;
	while (s[i] && !ft_isspace((unsigned char)s[i]))
	{
		if (!is_assign && is_special_char(s[i])
			&& (i == 0 || s[i - 1] != '\\'))
			break ;
		if (s[i] == '\'' || s[i] == '"')
		{
			tmp = handle_quotes(s, &i);
			if (tmp == -1)
				return (-1);
		}
		else
			i++;
	}
	return (i);
}

int	get_token_length(const char *s)
{
	int		i;
	int		is_assign;

	i = 0;
	if (!s[i])
		return (0);
	is_assign = check_assignment(s);
	if (is_special_char(s[0]) && !is_assign)
		return (get_operator_len(s));
	if (s[i] == '\'' || s[i] == '"')
		return (handle_quotes(s, &i));
	return (handle_word(s, is_assign));
}