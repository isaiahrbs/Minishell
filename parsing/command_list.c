/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:16:25 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/09 22:16:45 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	build(t_command **curr, t_token *token, t_command **head)
{
	t_command	*node;

	if (!*curr || is_metachar_type((*curr)->type))
	{
		node = cmd_new(token->value, token->type);
		if (!node)
			return (0);
		cmd_list_add_back(head, node);
		*curr = node;
	}
	else
		cmd_add_arg(*curr, token->value);
	return (1);
}

static t_command	*build_cmd_list(t_data *data)
{
	t_command	*head;
	t_command	*curr;
	t_command	*node;
	t_token		*token;

	head = NULL;
	curr = NULL;
	token = data->token;
	while (token)
	{
		if (is_metachar_type(token->type))
		{
			node = cmd_new(token->value, token->type);
			if (!node)
				return (head);
			cmd_list_add_back(&head, node);
			curr = node;
		}
		else
			if (!build(&curr, token, &head))
				return (head);
		token = token->next;
	}
	return (head);
}

void	command_list(t_data *data)
{
	if (data->activation_key)
	{
		update_token_types(data);
		data->commands = build_cmd_list(data);
	}
}
