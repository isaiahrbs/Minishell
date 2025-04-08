<<<<<<< Updated upstream

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:46:06 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/07 12:46:10 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> Stashed changes

#include "../../inc/minishell.h"

void	free_command_list(t_data *data)
{
	t_command	*temp;

	while (data->commands)
	{
		temp = data->commands;
		data->commands = data->commands->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
