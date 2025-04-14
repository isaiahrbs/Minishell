/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:08:41 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/14 15:15:42 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	invalid_var(t_token *token)
{
	int		i;
	int		j;
	t_token	*tmp;

	tmp = token;
	while (tmp && (tmp->value))
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '$' && !is_single_quote(tmp->value, i)
				&& is_valid_name(tmp->value))
			{
				j = 0;
				while (tmp->value[i + j]
					&& !is_metachar_value(&tmp->value[i + j]))
					j++;
				if (!clean_var(i, j, tmp))
					return (0);
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

char	*search_exit_code(char *old, char *var_start, t_data *data)
{
	char	*new;
	char	*exit_code;
	int		content_len;
	int		remaining_len;

	exit_code = ft_itoa(data->exit_code);
	if (!exit_code)
		return (NULL);
	content_len = ft_strlen(exit_code);
	remaining_len = ft_strlen(var_start) - 1;
	new = ft_calloc
		(var_start - old + content_len + remaining_len, sizeof(char));
	if (!new)
	{
		free(exit_code);
		return (NULL);
	}
	ft_strncat(new, old, var_start - old - 1);
	ft_strncat(new, exit_code, content_len);
	ft_strncat(new, var_start + 1, ft_strlen(var_start) - 1);
	free(exit_code);
	exit_code = NULL;
	return (new);
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
	if (!tmp->content)
		tmp->content = "";
	new = ft_calloc(i + content_len + remaining_len, sizeof(char));
	if (!new)
		return (NULL);
	ft_strncat(new, old, i - 1);
	ft_strncat(new, tmp->content, content_len);
	ft_strncat(new, var_start + name_len, ft_strlen(var_start) - name_len);
	return (new);
}

int	expand(t_token *token, t_token *var, t_data *data)
{
	char	*var_start;
	int		i;

	i = 0;
	if (!token || !(token->value) || !var)
		return (1);
	while (token)
	{
		while (token->value && token->value[i])
		{
			if (!ft_strncmp(token->value, "$?\0", 3)
				&& !ft_exit_code(data, token))
				return (0);
			var_start = is_var(&token->value[i], &i);
			if (!var_start)
				break ;
			if (var_start
				&& !scan_var_list(var, &token->value, var_start, data))
				return (0);
			i++;
		}
		token = token->next;
	}
	return (1);
}
