/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:36:34 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/09 20:55:01 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	process_quote(const char *str, int *i, char quote)
{
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	is_fully_quoted(const char *str, int *quote_type)
{
	int		i;
	int		first_type;
	char	quote;

	i = 0;
	first_type = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quote = str[i];
		i++;
		if (!check_quote_type(quote, &first_type))
			return (0);
		if (!process_quote(str, &i, quote))
			return (0);
		if (str[i] && str[i] != '"' && str[i] != '\'')
			return (0);
	}
	*quote_type = first_type;
	return (1);
}

static void	remove_all_quotes(char *str)
{
	char	*read;
	char	*write;

	read = str;
	write = str;
	while (*read)
	{
		if (*read != '"' && *read != '\'')
			*write++ = *read;
		read++;
	}
	*write = '\0';
}

void	remove_useless_quotes(char *str, int *quote_type)
{
	int	detected_quote_type;

	detected_quote_type = 0;
	if (is_fully_quoted(str, &detected_quote_type))
	{
		*quote_type = detected_quote_type;
		if (str[1] == '\0')
			*str = '\0';
		else
			return ;
	}
	else
	{
		*quote_type = 0;
		remove_all_quotes(str);
	}
}
