/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:13:34 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/31 12:27:52 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_lstlast(t_token *token)
{
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void	ft_lstadd_back(t_token **head, t_token *new)
{
	t_token	*last_elem;

	if (!new || !head)
		return ;
	else if (!*head)
		*head = new;
	else
	{
		last_elem = ft_lstlast(*head);
		last_elem->next = new;
	}
}
