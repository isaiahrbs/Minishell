/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:57:46 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/10 00:25:56 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_token_types(t_data *data)
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

t_cmd	*cmd_new(char *val, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->value = ft_strdup(val);
	cmd->type = type;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	cmd_list_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

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

void	cmd_add_arg(t_cmd *cmd, char *arg)
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
