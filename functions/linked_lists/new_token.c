/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:04:51 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/07 12:47:28 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*create_token(char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = NO_TYPE;
	new->content = NULL;
	new->name = NULL;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*create_var(char *name, char *content)
{
	t_token	*new;

	if (!name || !content)
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->name = name;
	new->content = content;
	new->type = NO_TYPE;
	new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
