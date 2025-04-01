/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:52:51 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/01 11:08:50 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int delete_var(t_token **env_list, char *var)
{
	t_token	*curr;
	t_token	*prev;

	if (!env_list || !*env_list || !var)
		return (0);
	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->name, var, ft_strlen(var))
			&& curr->name[ft_strlen(var)] == '\0')
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free_token(&curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int unset_var(t_data *data)
{
	t_token	*token_tmp;
	int		unset;

	if (!data->token || !(data->token->value))
		return (0);
	unset = 0;
	token_tmp = data->token;
	while (token_tmp)
	{
		if (token_tmp->value && !ft_strncmp(token_tmp->value, "unset", 5)
			&& (!token_tmp->value[5] || token_tmp->value[5] == ' '))
		{
			unset = 1;
			free(token_tmp->value);
			token_tmp->value = NULL;
		}
		else if (token_tmp->value && unset)
		delete_var(&(data->env_list), token_tmp->value);
		token_tmp = token_tmp->next;
	}
	return (1);
}
