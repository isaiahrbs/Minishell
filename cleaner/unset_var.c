/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 11:52:51 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/31 14:22:16 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int delete_var(t_token **env_list, char *var_name)
{
	t_token	*curr;
	t_token	*prev;

	if (!env_list || !*env_list || !var_name)
		return (0);
	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->name, var_name, ft_strlen(var_name))
			&& curr->name[ft_strlen(var_name)] == '\0')
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
	int		is_unset_command;

	if (!data->token || !(data->token->value))
		return (0);
	is_unset_command = 0;
	token_tmp = data->token;
	while (token_tmp)
	{
		if (token_tmp->value && !ft_strncmp(token_tmp->value, "unset", 5) &&
			(!token_tmp->value[5] || token_tmp->value[5] == ' '))
		{
			is_unset_command = 1;
			free(token_tmp->value);
			token_tmp->value = NULL;
		}
		else if (token_tmp->value && is_unset_command)
		delete_var(&(data->env_list), token_tmp->value);
		token_tmp = token_tmp->next;
	}
	return (1);
}
/*
int	delete_var(t_token *token, t_token *var)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		found;

	if (!token || !(token->value) || !var)
		return (0);
	while (token)
	{
		found = 0;
		tmp = var;
		while (tmp)
		{
			if (!ft_strncmp(token->value, tmp->name, ft_strlen(tmp->name)))
			{
				tmp2 = tmp;
				found = 1;
			}
			tmp = tmp->next;
			if (found)
			{
				free_token(&tmp2);
				tmp2 = NULL;
			}
		}
		if (!found)
			return (1);
		token = token->next;
	}
	return (1);
}

int	unset_var(t_data *data)
{
	t_token	*token_tmp;
	int		unset;

	if (!data->token || !(data->token->value))
		return (0);
	unset = 0;
	token_tmp = data->token;
	while (token_tmp)
	{
		if (token_tmp->value && !ft_strncmp(token_tmp->value, "unset", 5))
		{
			unset = 1;
			free(token_tmp->value);
			token_tmp->value = NULL;
		}
		else if (token_tmp->value && unset)
		{
			delete_var(token_tmp, data->env_list);
			unset = 0;
		}
		token_tmp = token_tmp->next;
	}
	return (1);
}
 */