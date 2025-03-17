/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:22 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/04 03:08:17 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void free_token_list(t_token **head)
{
	t_token	*current;
	t_token	*temp;

	if (!head || !*head)
		return;
	current = *head;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->content)
		{
			free(temp->content);
			temp->content = NULL;
		}
		if (temp->name)
		{
			free(temp->name);
			temp->name = NULL;
		}
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
	}
	*head = NULL;
}
