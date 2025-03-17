/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:10:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/04 21:16:13 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//* mon code original mais javais aucune idée comment traité les "\'" et donner une index celon sa quote type
/*
? comment j'ai fais?
*ma logique c'etais que si j'a une string
!str = {"hello world"} | {"'"} | {'"'}
*je check quand il ya un " ou un ', si je tombe sur un " ou un ' je fais quote = a str[i] et je continue jusqu'a ske je tombe sur un char qui est pareil que quote et je remet quote a 0 pour stocker un nouveau
*et donc c'est un moyen parfait de stocker une string sans que ca fasse de bug
*/

/* void remove_useless_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;  // This will track if we're inside a quote or not

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
		{
			str[j] = str[i];  // Copy character to the new position
			j++;
		}
		i++;
	}
	str[j] = '\0';
}*/

/* static void	handle_quote(char *str, int i, int *j, char *quote, int *quote_type)
{
	if (*quote == 0)
	{
		*quote = str[i];
		if (str[i] == '\'')
			*quote_type = 1;
		else
			*quote_type = 2;
	}
	else if (str[i] == *quote)
		*quote = 0;
	else
		str[(*j)++] = str[i];
}

void	remove_useless_quotes(char *str, int *quote_type)
{
	int		i;
	int		j;
	char	quote;
	int		escaped;

	i = 0;
	j = 0;
	quote = 0;
	escaped = 0;
	while (str[i])
	{
		if (!escaped && str[i] == '\\' && quote != '\'')
			escaped = 1;
		else if ((str[i] == '"' || str[i] == '\'') && quote == 0)
			handle_quote(str, i, &j, &quote, quote_type);
		else if (str[i] == quote)
			quote = 0;
		else
		{
			str[j++] = str[i];
			escaped = 0;
		}
		i++;
	}
	str[j] = '\0';
} */

//* donc apres jai demander a chat et jai regarder, il ma fais ca mais en respectant ma logique

//* ce bout de code c'est chatgpt car jsuis nul en code :((((
int	check_quote_type(char quote, int *first_type)
{
	if (!(*first_type))//* if first quote encountered
	{
		if (quote == '\'')
			*first_type = 1;
		else if (quote == '"')
			*first_type = 2;
		else
			first_type = 0;
	}
	else if ((quote == '\'' && *first_type != 1)//* ce else if c'est chatgpt qui a fais
		|| (quote == '"' && *first_type != 2))
		return (0);
	return (1);
}

void	filter(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		current->quote_type = 0;//* dont know if it has quotes yet
		if (current->value)
			remove_useless_quotes(current->value, &current->quote_type);//* check if its quotes and remove them
		current = current->next;
	}
}
