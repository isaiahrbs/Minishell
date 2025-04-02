/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:08:41 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/02 01:55:08 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	invalid_var(t_token *token)
{
	int		i;
	int		j;
	char	*new;
	t_token	*tmp;

	new = NULL;
	tmp = token;
	while (tmp && (tmp->value))
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '$' && !is_single_quote(tmp->value, i))
			{
				j = 0;
				while (tmp->value[i + j] && !is_metachar_value(&tmp->value[i + j]))
					j++;
				new = ft_calloc(i + ft_strlen(&tmp->value[i + j]) + 1, sizeof(char));
				if (!new)
					return (0);
				ft_strncat(new, tmp->value, i);
				ft_strncat(new, &tmp->value[i + j], j);
				free(tmp->value);
				tmp->value = new;
				new = NULL;
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*is_var(char *value, int *index)
{
	int		i;
	char	*var_start;

	i = 0;
	var_start = NULL;
	if (value[0] == '\0')
		return (NULL);
	while (value[i] && value[i] != '$')
		i++;
	if (value[i] == '\0' || is_single_quote(value, i))
		return (NULL);
	*index = *index + i;
	var_start = &value[i + 1];
	return (var_start);
}

char	*search_replace(t_token *tmp, char *old, char *var_start)
{
	char	*new;
	int		i;
	int		name_len;
	int		content_len;
	int		remaining_len;

	name_len = ft_strlen(tmp->name);
	content_len = ft_strlen(tmp->content);
	remaining_len = ft_strlen(var_start) - name_len;
	i = var_start - old;
	if (ft_strncmp(tmp->name, &old[i], name_len))
		return (old);
	/* if (old[i + name_len] != '\0' && old[i + name_len] != ' '
			&& old[i + name_len] != 34 && old[i + name_len] != '$')
		return (old); */
	if (!tmp->content)
		tmp->content = "";
	new = ft_calloc(i + content_len + remaining_len, sizeof(char));
	if (!new)
		return (NULL);
	ft_strncat(new, old, i - 1);
	ft_strncat(new, tmp->content, content_len);
	ft_strncat(new, var_start + name_len, ft_strlen(var_start) - name_len);
	free(old);
	return (new);
}

int	expand(t_token *token, t_token *var, t_data *data)
{
	t_token	*tmp;
	char	*var_start;
	int		i;

	i = 0;
	if (!token || !(token->value) || !var)
		return (1);
	while (token)
	{
		while (token->value && token->value[i])
		{
			if (!ft_strncmp(token->value, "$?\0", 3))
			{
				free(token->value);
				token->value = ft_itoa(data->exit_code);
				if (!token->value)
					return (0);
			}
			var_start = is_var(&token->value[i], &i);
			if (var_start)
			{
				tmp = var;
				while (tmp)
				{
					if (tmp->name && tmp->content)
						token->value = search_replace
							(tmp, token->value, var_start);
					if (!token->value)
						return (0);
					tmp = tmp->next;
				}
			}
			else
				break ;
			i++;
		}
		token = token->next;
	}
	return (1);
}
