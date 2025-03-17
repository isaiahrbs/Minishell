/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chained_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:51:14 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/04 21:12:39 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*get_token_type_str(t_type type)
{
	if (type == AND)
		return "AND";
	else if (type == OR)
		return "OR";
	else if (type == BACKGROUND)
		return "BACKGROUND";
	else if (type == VARIABLE)
		return "VARIABLE";
	else if (type == SIMPLE_QUOTE)
		return "SIMPLE_QUOTE";
	else if (type == DOUBLE_QUOTE)
		return "DOUBLE_QUOTE";
	else if (type == WHITESPACES)
		return "WHITESPACES";
	else if (type == PIPE)
		return "PIPE";
	else if (type == ARGUMENT)
		return "ARGUMENT";
	else if (type == REDIRECT_IN)
		return "REDIRECT_IN";
	else if (type == REDIRECT_OUT)
		return "REDIRECT_OUT";
	else if (type == APPEND)
		return "APPEND";
	else if (type == HERE_DOC)
		return "HERE_DOC";
	else if (type == INVALID)
		return "INVALID";
	else if (type == EMPTY)
		return "EMPTY";
	else if (type == INCOMPLETE_STRING)
		return "INCOMPLETE_STRING";
	else if (type == NO_TYPE)
		return "NO_TYPE";
	else if (type == CMD)
		return "CMD";
	else
		return "UNKNOWN";
}

void	print_chained_list(t_token *head)
{
	while (head)
	{
		printf("-----------------\n");
		printf("|");
		printf(BLUE " %s, (%s) " RESET, head->value, get_token_type_str(head->type));
		printf("|");
		if (head->next)
			printf(" ->");
		printf("\n-----------------\n");
		head = head->next;
	}
}

void	print_variable_list(t_token *head)
{
	while (head && *head->name && *head->content)
	{
		printf("-----------------\n");
		printf("|");
		printf(BLUE "variable name: %s " RESET, head->name);
		printf("|\n");
		printf("|");
		printf(BLUE "variable value: %s " RESET, head->content);
		printf("|");
		if (head->next)
			printf(" ->");
		printf("\n-----------------\n");
		head = head->next;
	}
}
