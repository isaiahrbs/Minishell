/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:21:49 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/09 20:57:05 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_if_valid(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == OR)
		{
			printf("Error: Invalid prompt.\n");
			data->activation_key = 0;
			return ;
		}
		else if (token->next)
		{
			if (is_metachar_type(token->type)
				&& is_metachar_type(token->next->type))
			{
				printf("Error: Invalid prompt.\n");
				data->activation_key = 0;
				return ;
			}
		}
		token = token->next;
	}
	data->activation_key = 1;
}
