/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 23:08:41 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/05 13:48:41 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (value[i] == '\0')
		return (NULL);
	if (i > 0 && value[i] == '$' && value[i - 1] == 34)
	{
		*index = *index + i;
		var_start = &value[i + 1];
	}
	while (value[i] && value[i] != 34)
		i++;
	if (value[i] == '\0')
		return (NULL);
	return (var_start);
}

char	*search_replace(t_token *tmp, char *old, char *var_start)
{
	char	*new;
	int		i;

	i = var_start - old;
	if (ft_strncmp(tmp->name, &old[i], ft_strlen(tmp->name)))
		return (old);
	if (old[i + ft_strlen(tmp->name)] != 34)
		return (old);
	if (!tmp->content)
		tmp->content = "";
	new = ft_calloc((ft_len(old, 34) + ft_strlen(tmp->content)
				+ ft_len2(var_start) + 1), sizeof(char));
	if (!new)
		return (NULL);
	ft_strncat(new, old, ft_len(old, 34));
	ft_strncat(new, tmp->content, ft_strlen(tmp->content));
	ft_strncat(new, var_start + ft_len3(var_start), ft_len2(var_start));
	free(old);
	return (new);
}

int	expand(t_token *token, t_token *var)
{
	t_token	*tmp;
	char	*var_start;
	int		i;

	i = 0;
	if (!token || !(token->value) || !var)
		return (1);
	while (token)
	{
		while (token->value[i])
		{
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
					{
						//MALLOC ERROR --- free what needs to be freed
						return (0);
					}
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
