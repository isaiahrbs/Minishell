/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:43:37 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/18 03:52:26 by dimatayi         ###   ########.fr       */
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
	if (!assign_var(data))
	{
		//free data->token
		return (0);
	}
	if (!expand(data->token, data->temporary_var))
	{
		//free data->token
		return (0);
	}
	if (!expand(data->token, data->env_list))
	{
		//free data->token
		return (0);
	}
	if (!invalid_var(data->token))
	{
		//free data->token
		return (0);
	}
	return (1);
}

t_token	*tokenize(t_data *data)
{
	char	**token_list;

	data->token = NULL;
	token_list = metachar_split(data->input);
	if (!token_list)
		return (NULL);
	//print_list(token_list);
	data->token = form_token_list(token_list);
	free_list(token_list);
	if (!data->token)
		return (NULL);
	if (!ft_variable(data))
		return (NULL);
	filter(data->token);//* to remove useless quotes
	init_token_type(data->token);
	free(data->input);
	return (data->token);
}
