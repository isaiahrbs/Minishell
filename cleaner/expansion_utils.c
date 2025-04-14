/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:10:10 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/14 15:16:02 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	is_single_quote(char *s, int dollar_index)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] && i < dollar_index)
	{
		if (s[i] == 39)
			counter++;
		i++;
	}
	if (counter == 0 || counter % 2 == 0)
		return (0);
	return (1);
}

int	ft_exit_code(t_data *data, t_token *token)
{
	free(token->value);
	token->value = ft_itoa(data->exit_code);
	if (!token->value)
		return (0);
	return (1);
}

int	scan_var_list(t_token *var, char **value, char *var_start, t_data *data)
{
	t_token	*var_tmp;
	char	*value_tmp;

	var_tmp = var;
	value_tmp = *value;
	while (var_tmp)
	{
		if (var_start[0] == '?')
			value_tmp = search_exit_code(*value, var_start, data);
		else if (var_tmp->name && var_tmp->content)
			value_tmp = search_replace(var_tmp, *value, var_start);
		if (!value_tmp)
			return (0);
		if (ft_strncmp(*value, value_tmp, ft_strlen(*value)))
		{
			free(*value);
			*value = value_tmp;
			break ;
		}
		var_tmp = var_tmp->next;
	}
	return (1);
}

int	clean_var(int i, int j, t_token *tmp)
{
	char	*new;

	new = NULL;
	new = ft_calloc(i + ft_strlen(&tmp->value[i + j]) + 1, sizeof(char));
	if (!new)
		return (0);
	ft_strncat(new, tmp->value, i);
	ft_strncat(new, &tmp->value[i + j], j);
	free(tmp->value);
	tmp->value = new;
	new = NULL;
	return (1);
}
