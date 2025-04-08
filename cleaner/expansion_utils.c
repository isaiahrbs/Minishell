/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:10:10 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/07 13:03:45 by dimatayi         ###   ########.fr       */
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

int	scan_var_list(t_token **tmp, t_token *var, t_token *token, char *var_start)
{
	*tmp = var;
	while (*tmp)
	{
		if ((*tmp)->name && (*tmp)->content)
			token->value = search_replace
				(*tmp, token->value, var_start);
		if (!token->value)
			return (0);
		*tmp = (*tmp)->next;
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
