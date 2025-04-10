/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:43:37 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/10 17:16:23 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_token_type(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		init_type(current);
		current = current->next;
	}
}

t_token	*create_token_node(char *token, int index, t_token *prev)
{
	t_token	*new;

	new = create_token(token);
	if (!new)
		return (NULL);
	new->index = index;
	new->prev = prev;
	return (new);
}

t_token	*form_token_list(char **token_list)
{
	t_token	*head;
	t_token	*new;
	t_token	*temp;
	int		i;

	head = NULL;
	temp = NULL;
	i = 0;
	while (token_list[i])
	{
		new = create_token_node(token_list[i], i, temp);
		if (!new)
		{
			free_token_list(&head);
			return (NULL);
		}
		if (temp)
			temp->next = new;
		if (!head)
			head = new;
		temp = new;
		i++;
	}
	return (head);
}

int	ft_variable(t_data *data)
{
	if (!unset_var(data))
		return (0);
	if (!assign_var(data))
		return (0);
	if (!expand(data->token, data->temporary_var, data))
		return (0);
	if (!expand(data->token, data->env_list, data))
		return (0);
	if (!invalid_var(data->token))
		return (0);
	return (1);
}

t_token	*tokenize(t_data *data)
{
	char	**token_list;

	data->token = NULL;
	token_list = metachar_split(data->input);
	free(data->input);
	if (!token_list)
		return (NULL);
	data->token = form_token_list(token_list);
	free_list(token_list);
	if (!data->token)
		return (NULL);
	if (is_equal("export", data->token->value) != 0 && !data->token->next)
		ft_export(data);
	handle_cd_command(data);
	if (!ft_variable(data))
	{
		free_token_list(&data->token);
		return (NULL);
	}
	filter(data->token);
	init_token_type(data->token);
	return (data->token);
}
