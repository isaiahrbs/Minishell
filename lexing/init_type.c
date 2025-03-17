/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:42:29 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/16 16:59:08 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_special_type(t_token *token)
{
	if (is_substitution(token->value) == 1)
	{
		token->type = SUBSTITUTION;
		return (1);
	}
	else if (is_assignment(token->value) == 1)
	{
		token->type = ASSIGNMENT;
		return (1);
	}
	else if (is_expansion(token->value) == 1)
	{
		token->type = EXPANSION;
		return (1);
	}
	else if (token->value[0] == '$' && is_valid_name(token->value + 1) == 1)
	{
		token->type = VARIABLE;
		return (1);
	}
	else
		return (0);
}

static void	init_special_chars(t_token *token)
{
	if (!token->value)
		return ;
	if (is_equal(token->value, ">>") == 1)
		token->type = APPEND;
	else if (is_equal(token->value, ">") == 1)
		token->type = REDIRECT_OUT;
	else if (is_equal(token->value, "<<") == 1)
		token->type = HERE_DOC;
	else if (is_equal(token->value, "<") == 1)
		token->type = REDIRECT_IN;
	else if (is_equal(token->value, "&") == 1)
		token->type = AND;
	else if (is_equal(token->value, "||") == 1)
		token->type = OR;
	else if (is_equal(token->value, "|") == 1)
		token->type = PIPE;
	else if (is_special_type(token))
		return ;
	else if (token->quote_type == 2)
		token->type = DOUBLE_QUOTE;
	else if (token->quote_type == 1)
		token->type = SIMPLE_QUOTE;
	else
		token->type = CMD;
}

void	init_type(t_token *token)
{
	if (!token)
		return;
	/* if (token->type == NO_TYPE)
		init_commands(token); */
	if (token->type == NO_TYPE)
		init_special_chars(token);
	if (token->type == NO_TYPE)
		return;
}
