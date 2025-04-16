/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:10:16 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/16 17:41:57 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quote_type(char quote, int *first_type)
{
	if (!(*first_type))
	{
		if (quote == '\'')
			*first_type = 1;
		else if (quote == '"')
			*first_type = 2;
		else
			first_type = 0;
	}
	else if ((quote == '\'' && *first_type != 1)
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
		current->quote_type = 0;
		if (current->value)
			remove_useless_quotes(current->value, &current->quote_type);
		current = current->next;
	}
}
