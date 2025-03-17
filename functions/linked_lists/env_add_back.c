/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:23:09 by irobinso          #+#    #+#             */
/*   Updated: 2025/02/25 11:25:30 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_lstadd_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (!head || !new)
		return;
	if (*head == NULL)
	{
		*head = new;
		return;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}
