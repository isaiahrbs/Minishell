/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:16:25 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/18 03:00:19 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_token_types(t_data *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok)
	{
		if (!is_metachar_type(tok->type))
			tok->type = WORD;
		tok = tok->next;
	}
}

static t_command	*cmd_new(char *val, int type)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->value = ft_strdup(val);
	cmd->type = type;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

static void	cmd_list_add_back(t_command **head, t_command *new)
{
	t_command	*tmp;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

static void	cmd_add_arg(t_command *cmd, char *arg)
{
	char	*tmp;
	char	*new_val;

	tmp = ft_strjoin(cmd->value, " ");
	if (!tmp)
		return ;
	new_val = ft_strjoin(tmp, arg);
	free(tmp);
	if (!new_val)
		return ;
	free(cmd->value);
	cmd->value = new_val;
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
		{
			if (!curr || is_metachar_type(curr->type))
			{
				node = cmd_new(token->value, token->type);
				if (!node)
					return (head);
				cmd_list_add_back(&head, node);
				curr = node;
			}
			else
				cmd_add_arg(curr, token->value);
		}
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
