/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:46:06 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/10 16:25:13 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_command_list(t_data *data)
{
	t_cmd	*temp;

	while (data->commands)
	{
		temp = data->commands;
		data->commands = data->commands->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
