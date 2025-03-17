/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:17:40 by dimatayi          #+#    #+#             */
/*   Updated: 2025/03/04 04:21:14 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_assign(char *s, t_token **var)
{
	t_token	*var_tmp;
	char *name;
	char *content;

	name = ft_name(s);
	if (!name)
		return (0);
	content = ft_content(s);
	if (!content)
	{
		free(name);
		return (0);
	}
	var_tmp = create_var(name, content);
	if (!var_tmp)
	{
		free_token_list(var);
		return (0);
	}
	ft_lstadd_back(var, var_tmp);
	return (1);
}

int	assign_var(t_data *data)
{
	t_token	*token_tmp;
	int		exp;

	if (!data->token || !(data->token->value))
		return (0);
	exp = 0;
	token_tmp = data->token;
	while (token_tmp)
	{
		if (token_tmp->value && is_assignment(token_tmp->value))
		{
			if (exp)
			{
				exp = 0;
				if (!ft_assign(token_tmp->value, &data->env_list))
				{
					token_tmp->value = NULL;
					return (0);
				}
			}
			else
			{
				if (!ft_assign(token_tmp->value, &data->temporary_var))
				{
					token_tmp->value = NULL;
					return (0);
				}
			}
		}
		if (!ft_strncmp(token_tmp->value, "export", 6))
			exp = 1;
		token_tmp = token_tmp->next;
	}
	return (1);
}
